#include "pch.h"
#include "ReceivingThread.h"
#include <opencv2/opencv.hpp>
#include "MainFrm.h"

BOOL CReceivingThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}


int CReceivingThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ClientSocket.Create();
	m_ClientSocket.Connect(rSocketAddress, 1);
	BITMAPINFOHEADER lpbmi = { 40, 0, 0, 1, 24, BI_RGB };
	m_ClientSocket.SetSockOpt(TCP_NODELAY, "0", 0);
	int lpOptionValue = 100;
	m_ClientSocket.SetSockOpt(SO_RCVBUF, &lpOptionValue, 4);
	m_ClientSocket.Receive(&lpbmi.biWidth, 4);
	m_ClientSocket.Receive(&lpbmi.biHeight, 4);
	int nBufLen;
	int n;
	cv::Mat lpBits;
	HDC hdc = GetDC(AfxGetMainWnd()->GetSafeHwnd());
	CRect cRect;
	GetClientRect(GetMainWnd()->GetSafeHwnd(), cRect);
	int DestHeight = cRect.Height();
	int DestWidth = (double)cRect.Height() * lpbmi.biWidth / (-lpbmi.biHeight);
	while (running) {
		m_ClientSocket.Receive(&nBufLen, 4);
		std::vector<uchar> buf(nBufLen);
		n = 0;
		while (n < nBufLen)
			n += m_ClientSocket.Receive(&buf[0] + n, nBufLen - n);
		lpBits = cv::imdecode(buf, cv::IMREAD_COLOR);
		StretchDIBits(hdc, (lpbmi.biWidth - DestWidth) / 2, 0, DestWidth, DestHeight, 0, 0, lpBits.cols, lpBits.rows, lpBits.data, (BITMAPINFO*)&lpbmi, DIB_RGB_COLORS, SRCCOPY);
	}
	ReleaseDC(NULL, hdc);

	return CWinThread::Run();
}


int CReceivingThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ClientSocket.Close();

	return CWinThread::ExitInstance();
}
