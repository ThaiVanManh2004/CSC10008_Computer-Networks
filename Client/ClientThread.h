#pragma once
#include <afxwin.h>
class CClientThread :
    public CWinThread
{
public:
    CSocket m_ClientSocket;
    bool running = true;
    struct Socket {
        CString rSocketAddress;
        UINT rSocketPort;
    };
    int n = 0;
    Socket rSocket[10];
public:
    virtual BOOL InitInstance();
    virtual int Run();
};

