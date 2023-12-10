#include "pch.h"
#include "ReceivingThread.h"
#include <thread>

BOOL CReceivingThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}
void PrintScreen(BITMAPINFOHEADER bmiHeader, BYTE* lpvBits) {
	HDC hScreenDC = GetDC(AfxGetMainWnd()->GetSafeHwnd());

	StretchDIBits(hScreenDC, (GetSystemMetrics(SM_CXSCREEN) - bmiHeader.biWidth) / 2, 0,bmiHeader.biWidth, -bmiHeader.biHeight, 0, 0, bmiHeader.biWidth, -bmiHeader.biHeight, lpvBits, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(NULL, hScreenDC);
}
int CReceivingThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ReceivingSocket.Create(1, SOCK_DGRAM);
	m_ClientSocket.Create();
	UINT lpBuf;
	CString rSocketAddress;
	UINT rSocketPort;
	m_ReceivingSocket.ReceiveFrom(&lpBuf, 4, rSocketAddress, rSocketPort);
	//AfxMessageBox(rSocketAddress);
	//CString cString;
	//cString.Format(_T("%u"), lpBuf);
	//AfxMessageBox(cString);
	m_ClientSocket.Connect(rSocketAddress, lpBuf);
	CRect cRect;
	GetClientRect(GetMainWnd()->GetSafeHwnd(), cRect);
	BITMAPINFOHEADER bmiHeader = { 40, 0, 0, 1, 24, BI_RGB, 0 };
	double scale = (double)GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);
	bmiHeader.biHeight = -cRect.Height();
	bmiHeader.biWidth = (int)(cRect.Height() * scale);
	m_ClientSocket.Send(&bmiHeader.biWidth, sizeof(bmiHeader.biWidth));
	m_ClientSocket.Send(&bmiHeader.biHeight, sizeof(bmiHeader.biHeight));
	bmiHeader.biSizeImage = ((bmiHeader.biWidth * 24 + 31) & ~31) / 8 * (-bmiHeader.biHeight);
	BYTE* lpvBits = new BYTE[bmiHeader.biSizeImage];
	int nBufferSize = 100;
	m_ClientSocket.SetSockOpt(SO_RCVBUF, &nBufferSize, sizeof(nBufferSize), SOL_SOCKET);
	while (m_ClientSocket.Receive(NULL, 1, MSG_PEEK) == 0);
	while (true) {
		Sleep(10);
		while (m_ClientSocket.Receive(NULL, 1, MSG_PEEK) == 0);
		int nByteReceived = 0;
		while (nByteReceived < bmiHeader.biSizeImage) {
			int n= m_ClientSocket.Receive(lpvBits + nByteReceived, bmiHeader.biSizeImage - nByteReceived);
			nByteReceived += n;
		}
		PrintScreen(bmiHeader, lpvBits);
	}
	return CWinThread::Run();
}


int CReceivingThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinThread::ExitInstance();
}
