#include "pch.h"
#include "ServerSocket.h"
#include <Windows.h>


//void LMouseUp(int x, int y)
//{
//    INPUT input[2] = {};
//
//    // Thiết lập bản tin cho sự kiện nhấn nút chuột
//    input[0].type = INPUT_MOUSE;
//    input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
//    input[0].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
//    input[0].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
//    // Thiết lập bản tin cho sự kiện thả nút chuột
//    input[1].type = INPUT_MOUSE;
//    input[1].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
//    input[1].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
//    input[1].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
//    SendInput(2, input, sizeof(INPUT));
//}
//void RMouseUp(int x, int y)
//{
//    INPUT input[2] = {};
//
//    // Thiết lập bản tin cho sự kiện nhấn nút chuột
//    input[0].type = INPUT_MOUSE;
//    input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN;
//    input[0].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
//    input[0].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
//    // Thiết lập bản tin cho sự kiện thả nút chuột
//    input[1].type = INPUT_MOUSE;
//    input[1].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTUP;
//    input[1].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
//    input[1].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
//    SendInput(2, input, sizeof(INPUT));
//}
//void KeyUp(UINT nchar) {
//    INPUT input[2];
//
//    // Chuẩn bị sự kiện ấn phím
//    input[0].type = INPUT_KEYBOARD;
//    input[0].ki.wVk = nchar;
//    input[0].ki.dwFlags = 0;
//    // Chuẩn bị sự kiện thả phím
//    input[1].type = INPUT_KEYBOARD;
//    input[1].ki.wVk = nchar;
//    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
//
//    // Gửi sự kiện đến hệ thống
//    SendInput(2, input, sizeof(INPUT));
//}
//void SimulateMouseWheelAtPosition(int x, int y, int delta) {
//    // Lưu vị trí con trỏ chuột hiện tại
//    POINT originalPos;
//    GetCursorPos(&originalPos);
//
//    // Đặt vị trí con trỏ chuột tới tọa độ mới
//    SetCursorPos(x, y);
//
//    // Mô phỏng sự kiện lăn chuột
//    INPUT input[2] = {};
//    input[0].type = INPUT_MOUSE;
//    input[0].mi.dwFlags = MOUSEEVENTF_WHEEL;
//    input[0].mi.mouseData = delta;
//
//    input[1].type = INPUT_MOUSE;
//    input[1].mi.dwFlags = MOUSEEVENTF_WHEEL;
//    input[1].mi.mouseData = 0;
//
//    SendInput(2, input, sizeof(INPUT));
//
//    // Khôi phục vị trí con trỏ chuột gốc
//    SetCursorPos(originalPos.x, originalPos.y);
//}
void CServerSocket::OnReceive(int nErrorCode)
{
//	// TODO: Add your specialized code here and/or call the base class
//    char type;
//    Receive(&type, sizeof(type));
//    if (type == 'L')
//    {
//        int x, y;
//        Receive(&x, sizeof(x));
//        Receive(&y, sizeof(y));
//        LMouseUp(x, y);
//    }
//    if (type == 'R')
//    {
//        int x, y;
//        Receive(&x, sizeof(x));
//        Receive(&y, sizeof(y));
//        RMouseUp(x, y);
//    }
//    if (type == 'K')
//    {
//        UINT n;
//        Receive(&n, sizeof(n));
//        KeyUp(n);
//    }
//    if (type == 'W')
//    {
//        short zDelta;
//        int x, y;
//        Receive(&zDelta, sizeof(zDelta));
//        Receive(&x, sizeof(x));
//        Receive(&y, sizeof(y));
//        SimulateMouseWheelAtPosition(x, y, zDelta);
//    }
	CSocket::OnReceive(nErrorCode);
}