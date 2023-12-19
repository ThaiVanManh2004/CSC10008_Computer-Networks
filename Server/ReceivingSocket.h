#pragma once
#include <afxsock.h>
class CReceivingSocket :
    public CSocket
{
public:
    char lpBuf;
    int x, y;
public:
    virtual void OnReceive(int nErrorCode);
};

