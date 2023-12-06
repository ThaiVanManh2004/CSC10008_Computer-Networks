#include "pch.h"
#include "ServerSocket.h"
//
#include "Server.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
//
#define SEND_BUFFER_SIZE    4096

void CServerSocket::OnReceive(int nErrorCode)
{
    char buff[3];
    Receive(buff, 3);

    // Get the dimensions of the primary display
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(dm);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
    int width = dm.dmPelsWidth;
    int height = dm.dmPelsHeight;

    // Create a device context for the primary display
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);

    // Create a bitmap compatible with the primary display
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

    // Copy the contents of the primary display to the bitmap
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    // Save the bitmap to a BMP file
    const char* filename = "screenshot.bmp";
    BITMAPINFOHEADER bmpInfoHeader = { 0 };
    bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfoHeader.biWidth = width;
    bmpInfoHeader.biHeight = -height;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24;
    bmpInfoHeader.biCompression = BI_RGB;
    bmpInfoHeader.biSizeImage = ((width * bmpInfoHeader.biBitCount + 31) / 32) * 4 * height;

    BITMAPFILEHEADER bmpFileHeader = { 0 };
    bmpFileHeader.bfType = 'MB';
    bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + bmpInfoHeader.biSizeImage;

    std::ofstream outputFile(filename, std::ios::out | std::ios::binary);
    outputFile.write(reinterpret_cast<const char*>(&bmpFileHeader), sizeof(BITMAPFILEHEADER));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(BITMAPINFOHEADER));

    BYTE* pixels = new BYTE[bmpInfoHeader.biSizeImage];
    GetDIBits(hDC, hBitmap, 0, height, pixels, reinterpret_cast<BITMAPINFO*>(&bmpInfoHeader), DIB_RGB_COLORS);
    outputFile.write(reinterpret_cast<const char*>(pixels), bmpInfoHeader.biSizeImage);

    // Clean up
    outputFile.close();
    delete[] pixels;
    SelectObject(hDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);



    // return value
    BOOL bRet = TRUE;
    // used to monitor the progress of a sending operation
    int fileLength, cbLeftToSend;
    // pointer to buffer for sending data
    // (memory is allocated after sending file size)
    BYTE* sendData = NULL;

    CFile sourceFile;
    CFileException fe;
    BOOL bFileIsOpen = FALSE;

    if (!(bFileIsOpen = sourceFile.Open(L"screenshot.bmp",
        CFile::modeRead | CFile::typeBinary, &fe)))
    {
        TCHAR strCause[256];
        fe.GetErrorMessage(strCause, 255);
        TRACE("SendFileToRemoteRecipient encountered an error while opening the local file\n"
            "\tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
            fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError);

        /* you should handle the error here */

        bRet = FALSE;
        goto PreReturnCleanup;
    }

    // first send length of file

    fileLength = sourceFile.GetLength();
    fileLength = htonl(fileLength);

    cbLeftToSend = sizeof(fileLength);

    do
    {
        int cbBytesSent;
        BYTE* bp = (BYTE*)(&fileLength) + sizeof(fileLength) - cbLeftToSend;
        cbBytesSent = this->Send(bp, cbLeftToSend);

        // test for errors and get out if they occurred
        if (cbBytesSent == SOCKET_ERROR)
        {
            int iErr = ::GetLastError();
            TRACE("SendFileToRemoteRecipient returned a socket error while sending file length\n"
                "\tNumber of Bytes sent = %d\n"
                "\tGetLastError = %d\n", cbBytesSent, iErr);

            /* you should handle the error here */

            bRet = FALSE;
            goto PreReturnCleanup;
        }

        // data was successfully sent, so account
        // for it with already-sent data
        cbLeftToSend -= cbBytesSent;
    } while (cbLeftToSend > 0);


    // now send the file's data    
    sendData = new BYTE[SEND_BUFFER_SIZE];

    cbLeftToSend = sourceFile.GetLength();

    do
    {
        // read next chunk of SEND_BUFFER_SIZE bytes from file

        int sendThisTime, doneSoFar, buffOffset;

        sendThisTime = sourceFile.Read(sendData, SEND_BUFFER_SIZE);
        buffOffset = 0;

        do
        {
            doneSoFar = this->Send(sendData + buffOffset,
                sendThisTime);

            // test for errors and get out if they occurred
            if (doneSoFar == SOCKET_ERROR)
            {
                int iErr = ::GetLastError();
                TRACE("SendFileToRemoteRecipient returned a socket error  while sending chunked file data\n"
                    "\tNumber of Bytes sent = %d\n"
                    "\tGetLastError = %d\n", doneSoFar, iErr);

                /* you should handle the error here */

                bRet = FALSE;
                goto PreReturnCleanup;
            }

            // data was successfully sent,
            // so account for it with already-sent data

            buffOffset += doneSoFar;
            sendThisTime -= doneSoFar;
            cbLeftToSend -= doneSoFar;
        } while (sendThisTime > 0);

    } while (cbLeftToSend > 0);

PreReturnCleanup: // labelled goto destination

    delete[] sendData;

    if (bFileIsOpen)
        sourceFile.Close();



    CSocket::OnReceive(nErrorCode);
}
