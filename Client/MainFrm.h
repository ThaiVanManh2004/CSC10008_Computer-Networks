
// MainFrm.h : interface of the CMainFrame class
//
#pragma once
#include "ClientThread.h"
#include "ReceivingThread.h"
#include "SendingThread.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	DECLARE_DYNCREATE(CMainFrame)

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

//
public:
	CButton initButton;
	void OnInitButtonClicked();
	CButton exitButton;
	void OnExitButtonClicked();

	CSocket m_ClientSocket;
	CSocket m_SendingSocket;
	CClientThread m_ClientThread;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int Width;
	int Height;
	int buttonHeight;

	CButton cButton[10];
	int nButton = 0;
	afx_msg void OnButtonClicked(UINT nID);

	CReceivingThread m_ReceivingThread;
	CSendingThread m_SendingThread;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//
};