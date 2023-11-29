#include "pch.h"
#include "ServerSocket.h"


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//
	exit(0);
	//

	CSocket::OnAccept(nErrorCode);
}
