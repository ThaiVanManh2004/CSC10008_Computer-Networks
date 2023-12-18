#pragma once
#include <afxwin.h>
class CServerThread :
    public CWinThread
{
public:
    UINT rSocketPort;
    CSocket m_ServerSocket;
    bool running = true;
    char lpBuf = 1;
public:
    virtual BOOL InitInstance();
    virtual int Run();
};