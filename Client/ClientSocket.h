#pragma once
#include <afxsock.h>
//
#include "ReceivingSocket.h"
//
class CClientSocket :
    public CSocket
{
//
public:
    CReceivingSocket m_ReceivingSocket;
//
};

