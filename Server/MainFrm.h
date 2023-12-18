
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
//
#include "ServerThread.h"
#include "ServerSocket.h"
#include "SendingThread.h"
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
	CServerThread* m_pServerThread;
	CServerSocket m_ServerSocket;
	CSendingThread* m_pSendingThread;
//
};

