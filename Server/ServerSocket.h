#pragma once
#include <afxsock.h>
//
#include "SendingSocket.h"
#include "ReceivingSocket.h"
//
class CServerSocket :
    public CSocket
{
public:
    virtual void OnAccept(int nErrorCode);
//
    CSendingSocket m_SendingSocket;
    CReceivingSocket m_ReceivingSocket;
    virtual void OnReceive(int nErrorCode);
};

