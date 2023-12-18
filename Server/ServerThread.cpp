#include "pch.h"
#include "ServerThread.h"


BOOL CServerThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return TRUE;
}


int CServerThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ServerSocket.Create(0, SOCK_DGRAM);
	int nOptionLen = 5;
	m_ServerSocket.SetSockOpt(SO_SNDBUF, &nOptionLen, 4);
	m_ServerSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	while (running) {
		m_ServerSocket.SendTo(&lpBuf, 1, 1, NULL);
		m_ServerSocket.SendTo(&rSocketPort, 4, 1, NULL);
	}
	lpBuf = 0;
	while (m_ServerSocket.SendTo(&lpBuf, 1, 1, NULL) < 1);
	while (m_ServerSocket.SendTo(&rSocketPort, 4, 1, NULL) < 4);
	m_ServerSocket.Close();

	return CWinThread::Run();
}
