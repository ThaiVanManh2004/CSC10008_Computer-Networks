#pragma once
#include <afxsock.h>
class CSendingSocket :
    public CSocket
{
//
public:
    CString rSocketAddress;
    UINT rSocketPort;
//
};

