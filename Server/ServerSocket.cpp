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

void CServerSocket::OnReceive(int nErrorCode)
{
    char buff[3];
    Receive(buff, 3);

    // Chụp màn hình và lấy thông tin bitmap
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    // Tạo BITMAPINFOHEADER
    BITMAPINFOHEADER bmiHeader = { 0 };
    bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmiHeader.biWidth = width;
    bmiHeader.biHeight = -height;
    bmiHeader.biPlanes = 1;
    bmiHeader.biBitCount = 24; // 24-bit RGB
    bmiHeader.biCompression = BI_RGB;
    bmiHeader.biSizeImage = 0;
    // Tính kích thước dữ liệu ảnh
    int imageSize = ((width * 24 + 31) & ~31) / 8 * height;

    // Tạo mảng để lưu dữ liệu ảnh
    BYTE* imageData = new BYTE[imageSize];
    GetDIBits(hMemoryDC, hBitmap, 0, height, imageData, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS);
    //StretchDIBits(hScreenDC, 100, 100, 1000, 1000, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, imageData, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);
    // Gửi kích thước ảnh đến client
    this->Send(&imageSize, sizeof(imageSize));
    this->Send(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
    this->Send(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
     //Gửi dữ liệu ảnh đến client
     //Giải phóng bộ nhớ của mảng dữ liệu ảnh
    UINT nByteSent = 0;
    while (nByteSent<imageSize) {
        int n = this->Send(imageData + nByteSent, imageSize-nByteSent);
        nByteSent += n;
    }
    // Giải phóng bộ nhớ
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    delete[] imageData;
    CSocket::OnReceive(nErrorCode);
}
