#pragma once
#include <afxwin.h>
#include <afxsock.h>

class CSendingThread :
    public CWinThread
{
public:
    CSocket m_ServerSocket;
    CSocket m_SendingSocket;
    CSocket m_ReceivingSocket;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

