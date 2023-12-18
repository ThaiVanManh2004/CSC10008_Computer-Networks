#include "pch.h"
#include "ServerSocket.h"


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_pServerThread->running = false;
	m_pSendingThread->CreateThread();
	Accept(m_ReceivingSocket);
	Close();

	CSocket::OnAccept(nErrorCode);
}
