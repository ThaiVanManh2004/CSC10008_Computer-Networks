
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ServerSocket.h"
#include "ReceivingSocket.h"
#include "ServerThread.h"
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
public:
	CServerSocket m_ServerSocket;
	CReceivingSocket m_ReceivingSocket;
	CButton initButton;
	void OnInitButtonClicked();
	CButton exitButton;
	void OnExitButtonClicked();
	CServerThread* m_ServerThread;

	CSendingThread m_SendingThread;
	CReceivingThread m_ReceivingThread;
//
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};