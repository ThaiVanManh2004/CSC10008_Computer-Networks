
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ServerSocket.h"
#include "SendingThread.h"
#include "ReceivingThread.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	DECLARE_DYNCREATE(CMainFrame)

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
//
protected:
	CButton cButton;
	afx_msg void OnButtonClicked();
	CSendingThread m_SendingThread;
	CReceivingThread m_ReceivingThread;
	CServerSocket ServerSocket;
//
};