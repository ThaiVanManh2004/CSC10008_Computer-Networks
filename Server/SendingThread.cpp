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
	m_ServerSocket.Create(1);
	m_ServerSocket.Listen();
	m_ServerSocket.Accept(m_SendingSocket);
	m_ServerSocket.Close();
	m_SendingSocket.SetSockOpt(TCP_NODELAY, "0", 0);
	//int lpOptionValue = 100;
	//m_SendingSocket.SetSockOpt(SO_SNDBUF, &lpOptionValue, 4);
    BITMAPINFOHEADER lpbmi = { 40, GetSystemMetrics(SM_CXSCREEN), -GetSystemMetrics(SM_CYSCREEN), 1, 24, BI_RGB };
	m_SendingSocket.Send(&lpbmi.biWidth, 4);
	m_SendingSocket.Send(&lpbmi.biHeight, 4);
    std::vector<uchar> buf;
    cv::Mat lpBits = cv::Mat(-lpbmi.biHeight, lpbmi.biWidth, CV_8UC3);
	int n;
	HDC hScreenDC = GetDC(NULL);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, lpbmi.biWidth, -lpbmi.biHeight);
	SelectObject(hMemoryDC, hBitmap);
	while (running) {
		BitBlt(hMemoryDC, 0, 0, lpbmi.biWidth, -lpbmi.biHeight, hScreenDC, 0, 0, SRCCOPY);
        GetDIBits(hMemoryDC, hBitmap, 0, -lpbmi.biHeight, lpBits.data, (BITMAPINFO*)&lpbmi, DIB_RGB_COLORS);
		cv::imencode(".jpg", lpBits, buf);
		int nBufLen = buf.size();
        m_SendingSocket.Send(&nBufLen, 4);
		n = 0;
		while (n < nBufLen) 
			n += m_SendingSocket.Send((char*)&buf[0] + n, nBufLen - n);
	}
	DeleteObject(hBitmap);
	DeleteDC(hMemoryDC);
	ReleaseDC(NULL, hScreenDC);

	return CWinThread::Run();
}
