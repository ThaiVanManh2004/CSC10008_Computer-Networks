#pragma once
#include <afxsock.h>
#include "ServerThread.h"
#include "SendingThread.h"
#include "ReceivingSocket.h"
class CServerSocket :
    public CSocket
{
public:
    CServerThread* m_pServerThread;
    CSendingThread* m_pSendingThread;
    CReceivingSocket m_ReceivingSocket;
public:
    virtual void OnAccept(int nErrorCode);
};

