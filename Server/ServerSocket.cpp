#include "pch.h"
#include "ServerSocket.h"
//
#include "Server.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "MainFrm.h"
#include <string>
//
#define SEND_BUFFER_SIZE    4096

CServerSocket::CServerSocket() noexcept {
    bmiHeader.biWidth = GetSystemMetrics(SM_CXSCREEN);
    bmiHeader.biHeight = -GetSystemMetrics(SM_CYSCREEN);
    bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
    imageData = new BYTE[bmiHeader.biSizeImage];
}
CServerSocket::~CServerSocket() {
    delete[]imageData;
}
void CServerSocket::OnReceive(int nErrorCode)
{
    char buff[1];
    Receive(buff, 1);

    // Chụp màn hình và lấy thông tin bitmap
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, bmiHeader.biWidth, -bmiHeader.biHeight);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, hScreenDC, 0, 0, SRCCOPY);
    GetDIBits(hMemoryDC, hBitmap, 0, -bmiHeader.biHeight, imageData, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS);
    this->Send(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
    this->Send(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
    nByteSent = 0;
    while (nByteSent < bmiHeader.biSizeImage) {
        int n = this->Send(imageData + nByteSent, bmiHeader.biSizeImage - nByteSent);
        nByteSent += n;
    }
    // Giải phóng bộ nhớ
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    CSocket::OnReceive(nErrorCode);
}
