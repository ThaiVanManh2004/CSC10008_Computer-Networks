#include "pch.h"
#include "SendingThread.h"


BOOL CSendingThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}


int CSendingThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ClientSocket.Create(2, SOCK_DGRAM);
	m_ClientSocket.ReceiveFrom(NULL, 0, rSocketAddress, rSocketPort);

	return CWinThread::Run();
}


int CSendingThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinThread::ExitInstance();
}
