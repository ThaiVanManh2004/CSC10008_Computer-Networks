#pragma once
#include <afxwin.h>
class CReceivingThread :
    public CWinThread
{
public:
    CString rSocketAddress;
    CSocket m_ReceivingSocket;
    CSocket m_ClientSocket;
    bool running = true;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

