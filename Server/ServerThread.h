#pragma once
#include <afxwin.h>
class CServerThread :
    public CWinThread
{
public:
    UINT rSocketPort;
    bool running = true;
    bool b = false;
    CSocket m_SendingSocket;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

