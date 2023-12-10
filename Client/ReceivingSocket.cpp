#include "pch.h"
#include "ReceivingSocket.h"
//
#include "MainFrm.h"
//

void CReceivingSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//
	CSocket::OnReceive(nErrorCode);
}


void CReceivingSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	exit(0);
	CSocket::OnAccept(nErrorCode);
}
