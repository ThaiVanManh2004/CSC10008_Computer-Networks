#pragma once
#include <afxwin.h>
class CReceivingThread :
    public CWinThread
{
public:
    CSocket m_ServerSocket;
public:
    virtual BOOL InitInstance();
    virtual int Run();
    virtual int ExitInstance();
};

