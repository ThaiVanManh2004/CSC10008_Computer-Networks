#pragma once
#include <afxsock.h>
class CReceivingSocket :
    public CSocket
{
private:
    char lpBuf;
    int x, y;
public:
    virtual void OnReceive(int nErrorCode);
};

