#pragma once
#include <afxwin.h>
#include "ReceivingSocket.h"
class CReceivingThread :
    public CWinThread
{
public:
    CSocket m_ClientSocket;
    CReceivingSocket m_ReceivingSocket;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

