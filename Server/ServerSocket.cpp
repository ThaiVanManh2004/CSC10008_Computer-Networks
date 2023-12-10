#include "pch.h"
#include "ServerSocket.h"
#include <Windows.h>


void MouseClick(int x, int y) {
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

    // Gửi bản tin đầu vào
    SendInput(2, input, sizeof(INPUT));
}
void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
    int width;
	Receive(&width, sizeof(width));
    int height;
    Receive(&height, sizeof(height));
    MouseClick(width, height);
	CSocket::OnReceive(nErrorCode);
}