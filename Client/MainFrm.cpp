
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Client.h"

#include "MainFrm.h"

// CMainFrame
#include "afxwin.h"
#include <thread>
#include "ReceivingThread.h"


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	//
	ON_BN_CLICKED(IDC_BUTTON, OnButtonClicked)
	//
	//ON_COMMAND(ID_DISPLAY_IMAGE, OnDisplayImage) 
	//
END_MESSAGE_MAP()

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//
	cButton.Create(_T(""), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, IDC_BUTTON);
	cButton.ShowWindow(SW_SHOWMAXIMIZED);
	return 0;
}
void CMainFrame::OnStream() {

	std::thread thread_stream([&]() {
		((CClientApp*)AfxGetApp())->m_ClientSocket.OnStream();
		});
	thread_stream.detach();
}
//void PrintScreen(BITMAPINFOHEADER bmiHeader, BYTE* lpvBits) {
//	HDC hScreenDC = GetDC(AfxGetMainWnd()->GetSafeHwnd());
//
//	StretchDIBits(hScreenDC, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, lpvBits, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);
//
//	ReleaseDC(NULL, hScreenDC);
//}
void CMainFrame::OnButtonClicked() {
	CReceivingThread* thread = new CReceivingThread;
	thread->CreateThread();

	//CSocket ReceivingSocket;
	//ReceivingSocket.Create(1, SOCK_DGRAM);
	//CString rSocketAddress;
	//UINT rSocketPort;
	//UINT lpBuf;
	//ReceivingSocket.ReceiveFrom(&lpBuf, 4, rSocketAddress, rSocketPort);
	//AfxMessageBox(rSocketAddress);
	//CString cString;
	//cString.Format(_T("%u %u"), lpBuf, rSocketPort);
	//AfxMessageBox(cString);
	//CSocket ClientSocket;
	//ClientSocket.Create();
	//while(ClientSocket.Connect(rSocketAddress, lpBuf)==0);
	//AfxMessageBox(_T("Client"));
	//CRect cRect;
	//GetClientRect(cRect);
	//BITMAPINFOHEADER bmiHeader = { 40, 0, 0, 1, 24, BI_RGB, 0 };
	//bmiHeader.biWidth = cRect.Width();
	//ClientSocket.SendTo(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth), rSocketPort, rSocketAddress);
	//bmiHeader.biHeight = -cRect.Height();
	//ClientSocket.SendTo(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight), rSocketPort, rSocketAddress);
	//bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
	//BYTE* lpvBits = new BYTE[bmiHeader.biSizeImage];
	//int bufferSize = 1000;
	//ClientSocket.SetSockOpt(SO_RCVBUF, &bufferSize, sizeof(bufferSize), SOL_SOCKET);
	//int nByteReceived;
	//		nByteReceived = 0;
	//		while (nByteReceived < bmiHeader.biSizeImage) {
	//			nByteReceived += ClientSocket.ReceiveFrom(lpvBits + nByteReceived, (bmiHeader.biSizeImage - nByteReceived > 1000) ? 1000 : (bmiHeader.biSizeImage - nByteReceived), rSocketAddress, rSocketPort);
	//			CString str;
	//			str.Format(_T("%d"), nByteReceived);
	//			AfxMessageBox(str);
	//		}
	//		PrintScreen(bmiHeader, lpvBits);
		
		
	// 
	// 
	// 
	// 
	// 
	//if (((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket == INVALID_SOCKET)
	//	((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.Create(1, SOCK_DGRAM);
	//else {
	//	((CClientApp*)AfxGetApp())->m_ClientSocket.Create();
	//	((CClientApp*)AfxGetApp())->m_ClientSocket.Connect(((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.rSocketAddress, ((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.rSocketPort);
	//	((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.Close();
	//	AfxMessageBox(_T(""));
	//	OnStream();
	//}
}
//