
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
	ON_BN_CLICKED(1, OnInitButtonClicked)
	ON_BN_CLICKED(2, OnExitButtonClicked)
	//
END_MESSAGE_MAP()

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//
	initButton.Create(_T("INIT"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 1);
	initButton.ShowWindow(SW_MAXIMIZE);
	exitButton.Create(_T("EXIT"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 2);
	//

	return 0;
}

//
void CMainFrame::OnInitButtonClicked() {
	delete m_pServerThread;
	delete m_pSendingThread;

	m_ServerSocket.Create();
	CString rSocketAddress;
	m_pServerThread = new CServerThread;
	m_ServerSocket.m_pServerThread = m_pServerThread;
	m_ServerSocket.GetSockName(rSocketAddress, m_pServerThread->rSocketPort);
	m_pServerThread->CreateThread();
	m_ServerSocket.Listen();
	m_pSendingThread = new CSendingThread;
	m_ServerSocket.m_pSendingThread = m_pSendingThread;

	initButton.ShowWindow(SW_HIDE);
	exitButton.ShowWindow(SW_MAXIMIZE);
}
void CMainFrame::OnExitButtonClicked() {
	m_pServerThread->running = false;
	m_ServerSocket.Close();

	m_pSendingThread->running = false;
	m_ServerSocket.m_ReceivingSocket.Close();

	exitButton.ShowWindow(SW_HIDE);
	initButton.ShowWindow(SW_MAXIMIZE);
}
//