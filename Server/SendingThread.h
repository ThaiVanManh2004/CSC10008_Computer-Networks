#pragma once
#include <afxwin.h>
#include "ServerSocket.h"
#include "SendingSocket.h"
#include "ReceivingSocket.h"

class CSendingThread :
    public CWinThread
{
public:
    CServerSocket m_ServerSocket;
    CSendingSocket m_SendingSocket;
    CReceivingSocket m_ReceivingSocket;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

