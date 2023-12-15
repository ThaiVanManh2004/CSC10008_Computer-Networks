
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Client.h"

#include "MainFrm.h"

// CMainFrame
#include "ReceivingThread.h"


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	//
	ON_BN_CLICKED(1, OnInitButtonClicked)
	ON_BN_CLICKED(2, OnExitButtonClicked)
	ON_CONTROL_RANGE(BN_CLICKED, 3, 13, OnButtonClicked)
	ON_WM_MOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	//ON_WM_MOUSEMOVE()
	//
END_MESSAGE_MAP()
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//
	CRect ClientRect;
	GetClientRect(ClientRect);
	Height = ClientRect.Height();
	Width = ClientRect.Width();
	initButton.Create(_T("Init"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 1);
	initButton.ShowWindow(SW_MAXIMIZE);
	exitButton.Create(_T("Exit"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 2);
	for (int i = 0; i < 10; i++) {
		cButton[i].Create(_T(""), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 3 + i);
	}
	return 0;
}
void CMainFrame::OnInitButtonClicked() {
	m_ClientThread.CreateThread();
	initButton.ShowWindow(SW_HIDE);
	exitButton.ShowWindow(SW_MAXIMIZE);
}
void CMainFrame::OnExitButtonClicked() {
	//exitButton.ShowWindow(SW_HIDE);
	//initButton.ShowWindow(SW_MAXIMIZE);
}
void CMainFrame::OnButtonClicked(UINT nID) {
	for (int i = 0; i < 10; i++) {
		cButton[i].ShowWindow(SW_HIDE);
	}
	m_ClientSocket.Create(0, SOCK_DGRAM);
	m_ClientSocket.SendTo(NULL, 0, m_ClientThread.rSocket[nID - 3].rSocketPort, m_ClientThread.rSocket[nID - 3].rSocketAddress);
	m_ClientThread.ExitInstance();
	m_ReceivingThread.rSocketAddress = m_ClientThread.rSocket[nID - 3].rSocketAddress;
	m_ReceivingThread.CreateThread();
	m_SendingSocket.Create();
	m_SendingSocket.Connect(m_ClientThread.rSocket[nID - 3].rSocketAddress, 2);
}
//

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == NULL) {
		for (int i = 0; i < 10; i++) {
			cButton[i].ShowWindow(SW_HIDE);
		}
		if (m_ClientThread.n == 0)
			exitButton.ShowWindow(SW_MAXIMIZE);
		else {
			exitButton.ShowWindow(SW_HIDE);
			buttonHeight = Height / m_ClientThread.n;
			for (int i = 0; i < m_ClientThread.n; i++) {
				cButton[i].MoveWindow(CRect(0, i * buttonHeight, Width, (i + 1) * buttonHeight));
				cButton[i].SetWindowTextW(m_ClientThread.rSocket[i].rSocketAddress);
				cButton[i].ShowWindow(SW_SHOW);
			}
		}
	}

	return CFrameWndEx::PreTranslateMessage(pMsg);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) {
	char lpBuf = 0;
	m_SendingSocket.Send(&lpBuf, 1);
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
		m_SendingSocket.Send(&point.x, sizeof(point.x));
		m_SendingSocket.Send(&point.y, sizeof(point.y));
	}
}
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) {
	char lpBuf = 1;
	m_SendingSocket.Send(&lpBuf, 1);
}
void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) {
	char lpBuf = 2;
	m_SendingSocket.Send(&lpBuf, 1);
}
void CMainFrame::OnRButtonUp(UINT nFlags, CPoint point) {
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
