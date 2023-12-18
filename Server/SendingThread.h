#pragma once
#include <afxwin.h>
class CSendingThread :
    public CWinThread
{
public:
    CSocket m_ServerSocket;
    CSocket m_SendingSocket;
    bool running = true;
public:
    virtual BOOL InitInstance();
    virtual int Run();
};

