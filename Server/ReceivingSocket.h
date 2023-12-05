#pragma once
#include <afxsock.h>
class CReceivingSocket :
    public CSocket
{
//
public:
    CString rSocketAddress;
    UINT rSocketPort;
//
};