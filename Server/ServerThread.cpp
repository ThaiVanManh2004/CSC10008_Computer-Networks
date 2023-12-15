#include "pch.h"
#include "ServerThread.h"
#include "MainFrm.h"


BOOL CServerThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}


int CServerThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_SendingSocket.Create(0, SOCK_DGRAM);
	m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	int nOptionLen = 5;
	m_SendingSocket.SetSockOpt(SO_SNDBUF, &nOptionLen, 4);
	char lpBuf = 1;
	while (running) {
		m_SendingSocket.SendTo(&lpBuf, 1, 1, NULL);
		m_SendingSocket.SendTo(&rSocketPort, 4, 1, NULL);
	}
	if (b)
		PostMessage(((CMainFrame*)AfxGetMainWnd())->GetSafeHwnd(), NULL, NULL, NULL);
	else {
		lpBuf = 0;
		while (m_SendingSocket.SendTo(&lpBuf, 1, 1, NULL) < 1);
		while (m_SendingSocket.SendTo(&rSocketPort, 4, 1, NULL) < 4);
	}
	m_SendingSocket.Close();

	return CWinThread::Run();
}


int CServerThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	running = false;

	return CWinThread::ExitInstance();
}
