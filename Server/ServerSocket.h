#pragma once
#include <afxsock.h>
class CServerSocket :
    public CSocket
{
public:
    virtual void OnReceive(int nErrorCode);
};

