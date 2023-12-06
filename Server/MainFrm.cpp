
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Server.h"

#include "MainFrm.h"

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
void CMainFrame::OnButtonClicked() {
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_ReceivingSocket.Create();
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_ReceivingSocket.Listen();

	((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.Create(0, SOCK_DGRAM);
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_ReceivingSocket.GetSockName(((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketAddress, ((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort);
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);

	CString errorMessage;
	errorMessage.Format(_T("SendTo failed with error: %u"), ((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort);
	AfxMessageBox(errorMessage);
	while (((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket != INVALID_SOCKET) {
		((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.SendTo(&(((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort), sizeof(UINT), 1, NULL);
		AfxMessageBox(_T(""));
	}
}
//