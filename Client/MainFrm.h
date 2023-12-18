
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
//
#include "ClientThread.h"
#include "ReceivingThread.h"
//

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
	CButton cButton[10];
	int Width;
	int Height;
	int buttonHeight;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnButtonClicked(UINT nID);
	CSocket m_SendingSocket;
	CClientThread* m_pClientThread;
	CReceivingThread* m_pReceivingThread;
//
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

