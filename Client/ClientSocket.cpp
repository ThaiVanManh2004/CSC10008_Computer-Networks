
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


CClientSocket::CClientSocket() noexcept {

}
CClientSocket::~CClientSocket() {

}
void CClientSocket::OnStream() {
	while (true) {

		AfxMessageBox(_T("tvm"));
		int n = -1;
		while (n <= 0) {
			n = this->Receive(NULL, 0, MSG_PEEK);
			CString str;
			str.Format(_T("%d"), n);
			AfxMessageBox(str);
		}
		AfxMessageBox(_T("abc"));
		Sleep(8);
		Receive(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
		Receive(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));

		bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);

		if (newHeight == 0) {
			CRect rect;
			AfxGetMainWnd()->GetClientRect(&rect);
			double scaleX = (double)rect.Width() / (double)bmiHeader.biWidth;
			double scaleY = (double)rect.Height() / (double)(-bmiHeader.biHeight);
			double scale = min(scaleX, scaleY);
			newWidth = (int)(scale * bmiHeader.biWidth);
			newHeight = (int)(scale * (-bmiHeader.biHeight));
			((CMainFrame*)AfxGetMainWnd())->cButton.ShowWindow(SW_HIDE);

			// Chiếu ảnh lên màn hình

		}

		// Nhận dữ liệu ảnh từ server
		int nByteReceived = 0;
		while (nByteReceived < bmiHeader.biSizeImage) {
			int n = Receive(imageData + nByteReceived, bmiHeader.biSizeImage - nByteReceived);
			nByteReceived += n;
		}
		hScreenDC = GetDC(AfxGetMainWnd()->GetSafeHwnd());

		StretchDIBits(hScreenDC, (bmiHeader.biWidth - newWidth) / 2, 0, newWidth, newHeight, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, imageData, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);

		ReleaseDC(NULL, hScreenDC);
	}
	
}
//void CClientSocket::OnReceive(int nErrorCode)
//{
//	Sleep(8);
//	Receive(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
//	Receive(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
//
//	bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
//
//	if (newHeight == 0) {
//		CRect rect;
//		AfxGetMainWnd()->GetClientRect(&rect);
//		double scaleX = (double)rect.Width() / (double)bmiHeader.biWidth;
//		double scaleY = (double)rect.Height() / (double)(-bmiHeader.biHeight);
//		double scale = min(scaleX, scaleY);
//		newWidth = (int)(scale * bmiHeader.biWidth);
//		newHeight = (int)(scale * (-bmiHeader.biHeight));
//		((CMainFrame*)AfxGetMainWnd())->cButton.ShowWindow(SW_HIDE);
//
//		// Chiếu ảnh lên màn hình
//		
//	}
//	
//    // Nhận dữ liệu ảnh từ server
//	int nByteReceived = 0;
//	while (nByteReceived < bmiHeader.biSizeImage) {
//		int n = Receive(imageData + nByteReceived, bmiHeader.biSizeImage-nByteReceived);
//		nByteReceived += n;
//	}
//	hScreenDC = GetDC(AfxGetMainWnd()->GetSafeHwnd());
//	
//	StretchDIBits(hScreenDC, (bmiHeader.biWidth-newWidth)/2, 0, newWidth, newHeight, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, imageData, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);
//
//	ReleaseDC(NULL, hScreenDC);
//	CSocket::OnReceive(nErrorCode);
//}