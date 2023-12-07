
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Client.h"

#include "MainFrm.h"

// CMainFrame
#include "afxwin.h"



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
void CMainFrame::OnButtonClicked() {
	if (((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket == INVALID_SOCKET)
		((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.Create(1, SOCK_DGRAM);
	else {
		((CClientApp*)AfxGetApp())->m_ClientSocket.Create();
		((CClientApp*)AfxGetApp())->m_ClientSocket.Connect(((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.rSocketAddress, ((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.rSocketPort);
		((CClientApp*)AfxGetApp())->m_ClientSocket.Send("M", 1);
		((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.Close();
	}
}
//