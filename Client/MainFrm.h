
// MainFrm.h : interface of the CMainFrame class
//
#pragma once
#include "ReceivingThread.h"
#include <afxsock.h>

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
	CButton cButton;
	afx_msg void OnButtonClicked();
	CReceivingThread m_ReceivingThread;
	CSocket m_ClientSocket;
	CString rSocketAddress;
	UINT rSocketPort;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//
};