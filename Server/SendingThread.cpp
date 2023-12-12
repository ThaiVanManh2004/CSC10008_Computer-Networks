#include "pch.h"
#include "SendingThread.h"
#include <opencv2/opencv.hpp>

BOOL CSendingThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}


int CSendingThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ReceivingSocket.Create();
	CString rSocketAddress;
	UINT rSocketPort;
	m_ReceivingSocket.GetSockName(rSocketAddress, rSocketPort);
    m_SendingSocket.Create(0, SOCK_DGRAM);
	m_SendingSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	m_SendingSocket.SendTo(&rSocketPort, 4, 1, NULL);
	m_SendingSocket.Close();
    m_ReceivingSocket.Listen();
	m_ReceivingSocket.Accept(m_ServerSocket);
	m_ReceivingSocket.Close();
	m_ServerSocket.SetSockOpt(TCP_NODELAY, "0", 0);
	int lpOptionValue = INT_MAX;
	m_ServerSocket.SetSockOpt(SO_SNDBUF, &lpOptionValue, 4);
    BITMAPINFOHEADER lpbmi = { 40, GetSystemMetrics(SM_CXSCREEN), -GetSystemMetrics(SM_CYSCREEN), 1, 24, BI_RGB };
	m_ServerSocket.Send(&lpbmi.biWidth, 4);
	m_ServerSocket.Send(&lpbmi.biHeight, 4);
    std::vector<uchar> buf;
    cv::Mat lpBits = cv::Mat(-lpbmi.biHeight, lpbmi.biWidth, CV_8UC3);
	int n;
	HDC hScreenDC = GetDC(NULL);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, lpbmi.biWidth, -lpbmi.biHeight);
	SelectObject(hMemoryDC, hBitmap);
	while (true) {
        StretchBlt(hMemoryDC, 0, 0, lpbmi.biWidth, -lpbmi.biHeight, hScreenDC, 0, 0, lpbmi.biWidth, -lpbmi.biHeight, SRCCOPY);
        GetDIBits(hMemoryDC, hBitmap, 0, -lpbmi.biHeight, lpBits.data, (BITMAPINFO*)&lpbmi, DIB_RGB_COLORS);
        cv::imencode(".jpg", lpBits, buf);
        int nBufLen = buf.size();
        m_ServerSocket.Send(&nBufLen, 4);
		int n = 0;
		while (n < nBufLen) 
			n += m_ServerSocket.Send((char*)&buf[0] + n, nBufLen - n);
	}

	return CWinThread::Run();
}


int CSendingThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ServerSocket.Close();

	return CWinThread::ExitInstance();
}
