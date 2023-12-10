
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
	ON_WM_LBUTTONUP()
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
void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) {
	CWnd::OnLButtonUp(nFlags, point);
	CRect rect;
	GetClientRect(rect);
	double scale = (double)GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);
	int width = rect.Height() * scale;
	int height = rect.Height();
	if (point.x< (GetSystemMetrics(SM_CXSCREEN) - width) / 2 || point.x>(GetSystemMetrics(SM_CXSCREEN) - width) / 2 + width) {
		return;
	}
	else {
		point.x = point.x - (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		point.x = (double)point.x / width * GetSystemMetrics(SM_CXSCREEN);
		point.y = (double)point.y / height * GetSystemMetrics(SM_CYSCREEN);
		m_ClientSocket.SendTo(&point.x, sizeof(point.x), rSocketPort, rSocketAddress);
		m_ClientSocket.SendTo(&point.y, sizeof(point.y), rSocketPort, rSocketAddress);
	}
}
void CMainFrame::OnButtonClicked() {
	m_ReceivingThread.CreateThread();
	cButton.ShowWindow(SW_HIDE);
	AfxMessageBox(_T("Waiting"));
	m_ClientSocket.Create(2, SOCK_DGRAM);
	m_ClientSocket.ReceiveFrom(NULL, 0, rSocketAddress, rSocketPort);
	AfxMessageBox(rSocketAddress);
	CString str;
	str.Format(_T("%u"), rSocketPort);
	AfxMessageBox(str);
}
//