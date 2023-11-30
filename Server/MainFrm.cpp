
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
	((CServerApp*)AfxGetApp())->m_ServerSocket.Create();
	((CServerApp*)AfxGetApp())->m_ServerSocket.Listen();
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.Create(0, SOCK_DGRAM);
	((CServerApp*)AfxGetApp())->m_ServerSocket.GetSockName(((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketAddress, ((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort);
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	while (((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket != INVALID_SOCKET) {
		((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.SendTo(&(((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.rSocketPort), sizeof(UINT), 1, NULL);
		AfxMessageBox(_T(""));
	}
}
//