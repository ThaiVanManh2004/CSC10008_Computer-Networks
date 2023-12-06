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

    HDC hScreenDC = GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hScreenDC);

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

    BitBlt(hMemDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bmpInfoHeader;
    memset(&bmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
    bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24;
    bmpInfoHeader.biCompression = BI_RGB;
    bmpInfoHeader.biWidth = width;
    bmpInfoHeader.biHeight = -height; // negative height to indicate top-down DIB
    bmpInfoHeader.biSizeImage = ((width * 24 + 31) / 32) * 4 * height;

    // Calculate size of image data
    int imageSize = bmpInfoHeader.biSizeImage + sizeof(BITMAPINFOHEADER);

    // Send image size first
    this->Send(&imageSize, sizeof(int));

    // Send bitmap info header
    this->Send(&bmpInfoHeader, sizeof(BITMAPINFOHEADER));

    // Get DIB bits
    BYTE* bitmapData = new BYTE[imageSize];
    GetDIBits(hMemDC, hBitmap, 0, height, bitmapData + sizeof(BITMAPINFOHEADER), (BITMAPINFO*)&bmpInfoHeader, DIB_RGB_COLORS);

    // Send bitmap data
    this->Send(bitmapData, imageSize);

    // Cleanup
    delete[] bitmapData;
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hScreenDC);
    CSocket::OnReceive(nErrorCode);
}
