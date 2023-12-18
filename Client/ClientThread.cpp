#include "pch.h"
#include "ClientThread.h"
#include "MainFrm.h"


BOOL CClientThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}


int CClientThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ClientSocket.Create(1, SOCK_DGRAM);
	int nOptionLen = 5;
	m_ClientSocket.SetSockOpt(SO_RCVBUF, &nOptionLen, 4);
	char c;
	UINT lpBuf;
	CString rSocketAddress;
	UINT rSocketPort;
	while (running) {
		if (m_ClientSocket.ReceiveFrom(&c, 1, rSocketAddress, rSocketPort) < 1)
			continue;
		if (m_ClientSocket.ReceiveFrom(&lpBuf, 4, rSocketAddress, rSocketPort) < 4)
			continue;
		if (c == 1) {
			bool b = true;
			for (int i = 0; i < n; i++)
				if (lpBuf == rSocket[i].rSocketPort) {
					b = false;
					break;
				}
			if (b == true) {
				rSocket[n].rSocketAddress = rSocketAddress;
				rSocket[n].rSocketPort = lpBuf;
				n++;
				PostMessage(((CMainFrame*)AfxGetMainWnd())->GetSafeHwnd(), NULL, NULL, NULL);
			}
		}
		if (c == 0) {
			int i = 0;
			while (lpBuf != rSocket[i].rSocketPort)
				i++;
			while (i < n - 1) {
				rSocket[i] = rSocket[i + 1];
				i++;
			}
			n--;
			PostMessage(((CMainFrame*)AfxGetMainWnd())->GetSafeHwnd(), NULL, NULL, NULL);
		}
	}
	m_ClientSocket.Close();

	return CWinThread::Run();
}

