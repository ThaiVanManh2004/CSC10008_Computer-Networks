
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Client.h"

#include "MainFrm.h"

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	//
	ON_BN_CLICKED(1, OnInitButtonClicked)
	ON_BN_CLICKED(2, OnExitButtonClicked)
	ON_CONTROL_RANGE(BN_CLICKED, 3, 13, OnButtonClicked)
	//
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//
	initButton.Create(_T("INIT"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 1);
	initButton.ShowWindow(SW_MAXIMIZE);
	exitButton.Create(_T("EXIT"), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 2);
	for (int i = 0; i < 10; i++)
		cButton[i].Create(_T(""), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, 3 + i);
	//

	return 0;
}

//
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == NULL)
		for (int i = 0; i < 10; i++) {
			cButton[i].ShowWindow(SW_HIDE);
		if (m_pClientThread->n == 0)
			exitButton.ShowWindow(SW_MAXIMIZE);
		else {
			exitButton.ShowWindow(SW_HIDE);
			buttonHeight = Height / m_pClientThread->n;
			for (int i = 0; i < m_pClientThread->n; i++) {
				cButton[i].MoveWindow(CRect(0, i * buttonHeight, Width, (i + 1) * buttonHeight));
				cButton[i].SetWindowTextW(m_pClientThread->rSocket[i].rSocketAddress);
				cButton[i].ShowWindow(SW_SHOW);
			}
		}
	}
	
	return CFrameWndEx::PreTranslateMessage(pMsg);
}
void CMainFrame::OnInitButtonClicked() {
	CRect ClientRect;
	GetClientRect(ClientRect);
	Height = ClientRect.Height();
	Width = ClientRect.Width();

	//delete m_pClientThread;
	//delete m_pReceivingThread;

	m_pClientThread = new CClientThread;
	m_pClientThread->CreateThread();

	initButton.ShowWindow(SW_HIDE);
	exitButton.ShowWindow(SW_MAXIMIZE);
}
void CMainFrame::OnExitButtonClicked() {
	m_pClientThread->running = false;
	m_SendingSocket.Create(0, SOCK_DGRAM);
	m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	char lpBuf = 2;
	for (int i = 1; i < 5; i++)
		m_SendingSocket.SendTo(&lpBuf, 1, 1, NULL);
	m_SendingSocket.Close();

	exitButton.ShowWindow(SW_HIDE);
	initButton.ShowWindow(SW_MAXIMIZE);
}
void CMainFrame::OnButtonClicked(UINT nID) {
	for (int i = 0; i < 10; i++)
		cButton[i].ShowWindow(SW_HIDE);

	m_pClientThread->running = false;

	m_pReceivingThread = new CReceivingThread;
	m_pReceivingThread->rSocketAddress = m_pClientThread->rSocket[nID - 3].rSocketAddress;
	m_pReceivingThread->CreateThread();

	m_SendingSocket.Create();
	m_SendingSocket.Connect(m_pClientThread->rSocket[nID - 3].rSocketAddress, m_pClientThread->rSocket[nID - 3].rSocketPort);
}
//


void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket == -1) {
		CFrameWndEx::OnClose();
	}
	else {
		m_pReceivingThread->running = false;
		char lpBuf = 0;
		m_SendingSocket.Send(&lpBuf, 1);
		m_SendingSocket.Close();
		Sleep(100);
		exitButton.ShowWindow(SW_HIDE);
		initButton.ShowWindow(SW_MAXIMIZE);
	}
}


void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 1;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
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
			while (m_SendingSocket.Send(&point.x, sizeof(point.x)) < sizeof(point.x));
			while (m_SendingSocket.Send(&point.y, sizeof(point.y)) < sizeof(point.y));
		}
	}
}


void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 2;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
	}
}


void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 3;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
	}
}


void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 4;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
	}
}


void CMainFrame::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 5;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
	}
}


void CMainFrame::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 6;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
	}
}


void CMainFrame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 7;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
	}
}


void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 8;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
		while (m_SendingSocket.Send(&nChar, sizeof(nChar)) < sizeof(nChar));
	}
}


void CMainFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 9;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
		while (m_SendingSocket.Send(&nChar, sizeof(nChar)) < sizeof(nChar));
	}
}


BOOL CMainFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (m_SendingSocket != -1) {
		char lpBuf = 10;
		while (m_SendingSocket.Send(&lpBuf, 1) < 1);
		while (m_SendingSocket.Send(&zDelta, sizeof(zDelta)) < sizeof(zDelta));
	}
	return TRUE;
}
