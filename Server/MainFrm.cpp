
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
	m_SendingThread.CreateThread();
	m_ReceivingThread.CreateThread();
}
//