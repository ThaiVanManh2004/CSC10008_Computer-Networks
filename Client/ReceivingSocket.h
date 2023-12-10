#pragma once
#include <afxsock.h>
class CReceivingSocket :
    public CSocket
{
public:
    virtual void OnReceive(int nErrorCode);
//
    UINT lpBuff;
    CString rSocketAddress;
    UINT rSocketPort;
    virtual void OnAccept(int nErrorCode);
};

