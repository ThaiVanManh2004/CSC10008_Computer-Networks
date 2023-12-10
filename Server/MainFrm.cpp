
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Server.h"

#include "MainFrm.h"
#include <thread>
#include <Windows.h>
#include "ReceivingSocket.h"
#include "ServerSocket.h"
#include "SendingSocket.h"
#include "SendingThread.h"
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	//
	ON_BN_CLICKED(IDC_BUTTON, OnButtonClicked)
	//
END_MESSAGE_MAP()

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//
	cButton.Create(_T(""), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, IDC_BUTTON);
	cButton.ShowWindow(SW_SHOWMAXIMIZED);
	//
	return 0;
}
//

void CMainFrame::OnStream() {
	std::thread thread_stream([&]() {
		((CServerApp*)AfxGetApp())->m_ServerSocket.OnStream();
	});
	thread_stream.detach();
}
void CMainFrame::OnButtonClicked() {






	CSendingThread* thread = new CSendingThread;
		thread->CreateThread();
	//	while (true) {

	//		CString str;
	//		str.Format(_T("%d"), thread->n);
	//		AfxMessageBox(str);
	//	}
	//CSocket SendingSocket;
	//SendingSocket.Create(0, SOCK_DGRAM);
	//CSocket ReceivingSocket;
	//ReceivingSocket.Create();
	//CString rSocketAddress;
	//UINT rSocketPort;
	//ReceivingSocket.GetSockName(rSocketAddress, rSocketPort);
	//CString str;
	//str.Format(_T("%u"), rSocketPort);
	//AfxMessageBox(str);
	//SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	//SendingSocket.SendTo(&rSocketPort, 4, 1, NULL);
	//CSocket ServerSocket;
	//while (ReceivingSocket.Accept(ServerSocket) == 0);
	//AfxMessageBox(_T("Server"));




	//BITMAPINFOHEADER bmiHeader = { 40, 0, 0, 1, 24, BI_RGB, 0 };
	//ServerSocket.ReceiveFrom(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth), rSocketAddress, rSocketPort);
	//ServerSocket.Receive(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
	//bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
	//AfxMessageBox(rSocketAddress);
	//BOOL bBroadcast = FALSE;
	//ServerSocket.SetSockOpt(SO_BROADCAST, &bBroadcast, sizeof(bBroadcast), SOL_SOCKET);
	//int bufferSize = 1000;
	//ServerSocket.SetSockOpt(SO_SNDBUF, &bufferSize, sizeof(bufferSize), SOL_SOCKET);
	//BYTE* lpvBits = new BYTE[bmiHeader.biSizeImage];
	//AfxMessageBox(_T("Waiting"));
	//		CapScreen(bmiHeader, lpvBits);
	//		int nByteSent = 0;
	//		while (nByteSent < bmiHeader.biSizeImage) {
	//			nByteSent += ServerSocket.SendTo(lpvBits + nByteSent, (bmiHeader.biSizeImage - nByteSent > 1000) ? 1000 : (bmiHeader.biSizeImage - nByteSent), 1, rSocketAddress);
	//			if (nByteSent % 10000 == 0) Sleep(1);
	//		}
	//		CString str;
	//		str.Format(_T("%d"), nByteSent);
	//		AfxMessageBox(str);

	//CString cString;
	//cString.Format(_T("%d %d"), nByteSent, bmiHeader.biSizeImage);
	//AfxMessageBox(cString);
	//delete[]lpvBits;





	//((CServerApp*)AfxGetApp())->m_ServerSocket.m_ReceivingSocket.Create();
	//((CServerApp*)AfxGetApp())->m_ServerSocket.m_ReceivingSocket.Listen();

	//((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.Create(0, SOCK_DGRAM);
	//((CServerApp*)AfxGetApp())->m_ServerSocket.m_ReceivingSocket.GetSockName(((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketAddress, ((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort);
	//((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);

	//CString errorMessage;
	//errorMessage.Format(_T("SendTo failed with error: %u"), ((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort);
	//AfxMessageBox(errorMessage);
	//while (((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket != INVALID_SOCKET) {
	//	((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.SendTo(&(((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort), sizeof(UINT), 1, NULL);
	//}
}

//