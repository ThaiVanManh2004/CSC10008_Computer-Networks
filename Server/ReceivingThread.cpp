#include "pch.h"
#include "ReceivingThread.h"


BOOL CReceivingThread::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return true;
}

void LMouseUp(int x, int y)
{
	INPUT input[2] = {};

	// Thiết lập bản tin cho sự kiện nhấn nút chuột
	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
	input[0].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
	input[0].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
	// Thiết lập bản tin cho sự kiện thả nút chuột
	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
	input[1].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
	input[1].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
	SendInput(2, input, sizeof(INPUT));
}
void RMouseUp(int x, int y)
{
	INPUT input[2] = {};

	// Thiết lập bản tin cho sự kiện nhấn nút chuột
	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN;
	input[0].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
	input[0].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
	// Thiết lập bản tin cho sự kiện thả nút chuột
	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTUP;
	input[1].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
	input[1].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
	SendInput(2, input, sizeof(INPUT));
}
void KeyUp(UINT nchar) {
	INPUT input[2];

	// Chuẩn bị sự kiện ấn phím
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = nchar;
	input[0].ki.dwFlags = 0;
	// Chuẩn bị sự kiện thả phím
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = nchar;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;

	// Gửi sự kiện đến hệ thống
	SendInput(2, input, sizeof(INPUT));
}

int CReceivingThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ServerSocket.Create(0, SOCK_DGRAM);
	m_ServerSocket.SetSockOpt(SO_BROADCAST, "0", 0);
	m_ServerSocket.SendTo(NULL, 0, 2, NULL);
	char lpBuf;
	while (true) {
		m_ServerSocket.Receive(&lpBuf, 1);
		if (lpBuf == 'L') {
			int x;
			int y;
			m_ServerSocket.Receive(&x, 4);
			m_ServerSocket.Receive(&y, 4);
			LMouseUp(x, y);
		}
		if (lpBuf == 'R') {
			int x;
			int y;
			m_ServerSocket.Receive(&x, 4);
			m_ServerSocket.Receive(&y, 4);
			RMouseUp(x, y);
		}
		if (lpBuf == 'K') {
			UINT nChar;
			m_ServerSocket.Receive(&nChar, 4);
			KeyUp(nChar);
		}
	}

	return CWinThread::Run();
}


int CReceivingThread::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinThread::ExitInstance();
}
