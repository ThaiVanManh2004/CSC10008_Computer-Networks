#include "pch.h"
#include "ReceivingSocket.h"
//
#include "MainFrm.h"
//
#define IDC_IMAGE                 1013

void CReceivingSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//
	ReceiveFrom(&lpBuff, sizeof(UINT), rSocketAddress, rSocketPort);
	CString errorMessage;
	errorMessage.Format(_T("SendTo failed with error: %u"), lpBuff);
	AfxMessageBox(errorMessage);
	rSocketPort = lpBuff;
	
	((CMainFrame*)AfxGetMainWnd())->cButton.SetWindowTextW(rSocketAddress);
	//
	
	CSocket::OnReceive(nErrorCode);
}
