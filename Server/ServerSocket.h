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
    CServerSocket() noexcept;
    virtual ~CServerSocket();
public:
    CSendingSocket m_SendingSocket;
    CReceivingSocket m_ReceivingSocket;
    //virtual void OnReceive(int nErrorCode);
    void OnStream();

    BITMAPINFOHEADER bmiHeader = { 40, 0,0,1,24,BI_RGB,0 };
    BYTE* imageData;
    UINT nByteSent;
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, bmiHeader.biWidth, -bmiHeader.biHeight);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
};

