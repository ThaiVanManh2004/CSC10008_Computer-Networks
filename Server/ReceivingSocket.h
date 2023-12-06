#pragma once
#include <afxsock.h>
class CReceivingSocket :
    public CSocket
{
public:
    virtual void OnAccept(int nErrorCode);
};