#include "pch.h"
#include "ReceivingSocket.h"

#include "Server.h"

void CReceivingSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	Accept(((CServerApp*)AfxGetApp())->m_ServerSocket);
	((CServerApp*)AfxGetApp())->m_ServerSocket.m_SendingSocket.Close();
	this->Close();
	CSocket::OnAccept(nErrorCode);
}
