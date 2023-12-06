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
    CSendingSocket m_SendingSocket;
    CReceivingSocket m_ReceivingSocket;
    virtual void OnReceive(int nErrorCode);
};

