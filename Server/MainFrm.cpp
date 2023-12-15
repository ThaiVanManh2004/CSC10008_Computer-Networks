
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
	initButton.Create(_T("Init"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 1);
	initButton.ShowWindow(SW_MAXIMIZE);
	exitButton.Create(_T("Exit"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 2);
	//
	return 0;
}
//
void CMainFrame::OnInitButtonClicked() {
	m_ServerSocket.Create(0, SOCK_DGRAM);
	CString rSocketAddress;
	delete m_ServerThread;
	m_ServerThread = new CServerThread;
	m_ServerSocket.GetSockName(rSocketAddress, m_ServerThread->rSocketPort);
	m_ServerThread->CreateThread();
	initButton.ShowWindow(SW_HIDE);
	exitButton.ShowWindow(SW_MAXIMIZE);
}
void CMainFrame::OnExitButtonClicked() {
	m_ServerThread->ExitInstance();
	m_ServerSocket.Close();
	exitButton.ShowWindow(SW_HIDE);
	initButton.ShowWindow(SW_MAXIMIZE);
}
//

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == NULL) {
		m_SendingThread.CreateThread();
		CSocket m_ServerSocket;
		m_ServerSocket.Create(2);
		m_ServerSocket.Listen();
		m_ServerSocket.Accept(m_ReceivingSocket);
	}

	return CFrameWndEx::PreTranslateMessage(pMsg);
}
