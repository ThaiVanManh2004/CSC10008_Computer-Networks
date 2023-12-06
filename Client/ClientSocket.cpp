
#include "pch.h"
#include "ClientSocket.h"
#include "Client.h"
#define RECV_BUFFER_SIZE 4096
#define IDC_IMAGE 1013
#include "afxdialogex.h"
#include <afxwin.h>
#include <afxcmn.h>

#include <Windows.h>
#include <string>
#include <atlimage.h>  // for CImage
#include <gdiplus.h>
#include "MainFrm.h"

void CClientSocket::OnReceive(int nErrorCode)
{
    int imageSize;
    this->Receive(&imageSize, sizeof(int)); // Nhận kích thước dữ liệu ảnh

    BITMAPINFOHEADER bmpInfoHeader;
    this->Receive(&bmpInfoHeader, sizeof(BITMAPINFOHEADER)); // Nhận thông tin header của bitmap

    int width = bmpInfoHeader.biWidth;
    int height = abs(bmpInfoHeader.biHeight);

    // Nhận dữ liệu ảnh
    BYTE* bitmapData = new BYTE[imageSize];
    this->Receive(bitmapData, imageSize);

    // Hiển thị ảnh lên màn hình
    HDC hDC = GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hDC, width, height);

    SetDIBits(hMemDC, hBitmap, 0, height, bitmapData + sizeof(BITMAPINFOHEADER), (BITMAPINFO*)&bmpInfoHeader, DIB_RGB_COLORS);

    StretchBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, width, height, SRCCOPY);

    // Giải phóng tài nguyên
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hDC);
    delete[] bitmapData;
	((CClientApp*)AfxGetApp())->m_ClientSocket.Send("TVM", 3);
	// only close file if it's open (open might have failed above)


	
	CSocket::OnReceive(nErrorCode);
}
