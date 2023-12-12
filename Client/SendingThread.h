#pragma once
#include <afxwin.h>
class CSendingThread :
    public CWinThread
{
public:
    CSocket m_ClientSocket;
    CString rSocketAddress;
    UINT rSocketPort;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

