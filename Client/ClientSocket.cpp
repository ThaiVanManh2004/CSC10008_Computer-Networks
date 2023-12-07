
#include "pch.h"
#include "ClientSocket.h"
#include "Client.h"
#define RECV_BUFFER_SIZE 4096
#define IDC_IMAGE 1013
#include "afxdialogex.h"
#include <afxwin.h>
#include <afxcmn.h>

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <atlimage.h>  // for CImage
#include <gdiplus.h>
#include "MainFrm.h"

void CClientSocket::OnReceive(int nErrorCode)
{
	// Lấy thông tin bitmap từ dữ liệu nhận được
	BITMAPINFOHEADER bmiHeader = { 0 };
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24; // 24-bit RGB
	bmiHeader.biCompression = BI_RGB;
	bmiHeader.biSizeImage = 0;

    Receive(&bmiHeader.biSizeImage, sizeof(bmiHeader.biSizeImage));
	Receive(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
	Receive(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
    BYTE* imageData = new BYTE[bmiHeader.biSizeImage];
    // Nhận dữ liệu ảnh từ server
	int nByteReceived = 0;
	while (nByteReceived < bmiHeader.biSizeImage) {
		int n = Receive(imageData+nByteReceived, bmiHeader.biSizeImage-nByteReceived);
		nByteReceived += n;
	}
	// Chiếu ảnh lên màn hình
	((CMainFrame*)AfxGetMainWnd())->cButton.ShowWindow(SW_HIDE);
	CRect rect;
	((CMainFrame*)AfxGetMainWnd())->GetClientRect(&rect);
	double scaleX = (double)rect.Width() / (double)bmiHeader.biWidth;
	double scaleY = (double)rect.Height() / (double)(-bmiHeader.biHeight);
	double scale = min(scaleX, scaleY);
	int newWidth = (int)(scale * bmiHeader.biWidth);
	int newHeight = (int)(scale * (-bmiHeader.biHeight));
	HWND hWnd = FindWindow(NULL, _T("DMP Client"));
	HDC hScreenDC = GetDC(hWnd);
	int n = StretchDIBits(hScreenDC, (bmiHeader.biWidth-newWidth)/2, 0, newWidth, newHeight, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, imageData, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);
	

 //   // Giải phóng bộ nhớ của mảng dữ liệu ảnh
    delete[] imageData;
	//Sleep(3000);
	((CClientApp*)AfxGetApp())->m_ClientSocket.Send("TVM", 3);

	//
	CSocket::OnReceive(nErrorCode);
}
