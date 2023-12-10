#include "pch.h"
#include "SendingThread.h"


BOOL CSendingThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}


void CapScreen(BITMAPINFOHEADER bmiHeader, BYTE* lpvBits) {
	HDC hScreenDC = GetDC(NULL);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, bmiHeader.biWidth, -bmiHeader.biHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
	StretchBlt(hMemoryDC, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, hScreenDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SRCCOPY);
	GetDIBits(hMemoryDC, hBitmap, 0, -bmiHeader.biHeight, lpvBits, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS);
}
int CSendingThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ReceivingSocket.Create();
	m_ReceivingSocket.Listen();
	UINT rSocketPort;
	CString rSocketAddress;
	m_SendingSocket.Create(0, SOCK_DGRAM);
	m_ReceivingSocket.GetSockName(rSocketAddress, rSocketPort);
	m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	m_SendingSocket.SendTo(&rSocketPort, 4, 1, NULL);
	m_ReceivingSocket.Accept(m_ServerSocket);
	BITMAPINFOHEADER bmiHeader = { 40, 0, 0, 1, 24, BI_RGB, 0 };
	m_ServerSocket.Receive(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
	m_ServerSocket.Receive(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
	bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
	BYTE* lpvBits = new BYTE[bmiHeader.biSizeImage];
	while (true) {

		CapScreen(bmiHeader, lpvBits);
		int nByteSent = 0;
		while (nByteSent < bmiHeader.biSizeImage) {
			nByteSent += m_ServerSocket.Send(lpvBits + nByteSent, bmiHeader.biSizeImage - nByteSent);
		}
	}
	//CString str;
	//str.Format(_T("%d"), nByteSent);
	//AfxMessageBox(str);
	//BITMAPINFOHEADER bmiHeader = { 40, 0, 0, 1, 24, BI_RGB, 0 };
	//ServerSocket.ReceiveFrom(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth), rSocketAddress, rSocketPort);
	//ServerSocket.Receive(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
	//bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
	//AfxMessageBox(rSocketAddress);
	//BOOL bBroadcast = FALSE;
	//ServerSocket.SetSockOpt(SO_BROADCAST, &bBroadcast, sizeof(bBroadcast), SOL_SOCKET);
	//int bufferSize = 1000;
	//ServerSocket.SetSockOpt(SO_SNDBUF, &bufferSize, sizeof(bufferSize), SOL_SOCKET);
	//BYTE* lpvBits = new BYTE[bmiHeader.biSizeImage];
	return CWinThread::Run();
}


int CSendingThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinThread::ExitInstance();
}
