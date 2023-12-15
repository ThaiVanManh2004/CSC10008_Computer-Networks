#include "pch.h"
#include "ServerSocket.h"
#include "MainFrm.h"


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	this->Close();
	((CMainFrame*)AfxGetMainWnd())->m_ServerThread->b = true;
	((CMainFrame*)AfxGetMainWnd())->m_ServerThread->running = false;

	CSocket::OnReceive(nErrorCode);
}
