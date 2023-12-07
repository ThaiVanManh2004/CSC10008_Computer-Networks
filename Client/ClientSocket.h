#pragma once
#include <afxsock.h>
//
#include "ReceivingSocket.h"
//
class CClientSocket :
    public CSocket
{
public:
    CClientSocket() noexcept;
    virtual ~CClientSocket();
//
public:
    CReceivingSocket m_ReceivingSocket;
//
    virtual void OnReceive(int nErrorCode);
    BITMAPINFOHEADER bmiHeader = { 40, 0,0,1,24,BI_RGB,0 };

    BYTE imageData[6220800];
    int newWidth;
    int newHeight = 0;
    HDC hScreenDC;
};

