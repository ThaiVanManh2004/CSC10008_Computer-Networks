
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
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	//ON_WM_MOUSEMOVE()
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
	char c = 'L';
	m_SendingThread.m_ClientSocket.SendTo(&c, sizeof(c), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
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
		m_SendingThread.m_ClientSocket.SendTo(&point.x, sizeof(point.x), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
		m_SendingThread.m_ClientSocket.SendTo(&point.y, sizeof(point.y), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
	}
}void CMainFrame::OnRButtonUp(UINT nFlags, CPoint point) {
	char c = 'R';
	m_SendingThread.m_ClientSocket.SendTo(&c, sizeof(c), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
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
		m_SendingThread.m_ClientSocket.SendTo(&point.x, sizeof(point.x), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
		m_SendingThread.m_ClientSocket.SendTo(&point.y, sizeof(point.y), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
	}
}
void CMainFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	char c = 'K';
	m_SendingThread.m_ClientSocket.SendTo(&c, sizeof(c), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);
	m_SendingThread.m_ClientSocket.SendTo(&nChar, sizeof(nChar), m_SendingThread.rSocketPort, m_SendingThread.rSocketAddress);

}
void CMainFrame::OnButtonClicked() {
	m_ReceivingThread.CreateThread();
	cButton.ShowWindow(SW_HIDE);
	m_SendingThread.CreateThread();
}
//