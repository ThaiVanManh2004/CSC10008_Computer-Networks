#pragma once
#include <afxsock.h>
//
#include "SendingSocket.h"
//
class CServerSocket :
    public CSocket
{
public:
    virtual void OnAccept(int nErrorCode);
//
    CSendingSocket m_SendingSocket;
};

