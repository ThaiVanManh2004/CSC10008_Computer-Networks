#include "pch.h"
#include "ReceivingSocket.h"
//
#include "MainFrm.h"
//


void CReceivingSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//
	ReceiveFrom(&lpBuff, sizeof(UINT), rSocketAddress, rSocketPort);
	rSocketPort = lpBuff;
	((CMainFrame*)AfxGetMainWnd())->cButton.SetWindowTextW(rSocketAddress);
	//

	CSocket::OnReceive(nErrorCode);
}
