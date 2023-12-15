#include "pch.h"
#include "ReceivingSocket.h"




void MouseMove(int x, int y) {
    // Tính tọa độ tương đối của chuột trên màn hình
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = x * (65535.0f / fScreenWidth);
    double fy = y * (65535.0f / fScreenHeight);

    // Tạo và cấu hình INPUT để di chuyển chuột đến tọa độ mới
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    input.mi.dx = static_cast<LONG>(fx);
    input.mi.dy = static_cast<LONG>(fy);

    // Gửi INPUT vào hệ thống
    ::SendInput(1, &input, sizeof(INPUT));
}
void LMouseDown() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = cursorPos.x * (65535.0f / fScreenWidth);
    double fy = cursorPos.y * (65535.0f / fScreenHeight);

    // Tạo và cấu hình INPUT để di chuyển chuột đến tọa độ mới và bấm chuột trái
    INPUT inputs = { 0 };

    // Bấm chuột trái
    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
    inputs.mi.dx = static_cast<LONG>(fx);
    inputs.mi.dy = static_cast<LONG>(fy);

    // Gửi INPUT vào hệ thống
    ::SendInput(1, &inputs, sizeof(INPUT));
}
void LMouseUp() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = cursorPos.x * (65535.0f / fScreenWidth);
    double fy = cursorPos.y * (65535.0f / fScreenHeight);

    // Tạo và cấu hình INPUT để di chuyển chuột đến tọa độ mới và bấm chuột trái
    INPUT inputs = { 0 };


    // Nhả chuột trái
    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
    inputs.mi.dx = static_cast<LONG>(fx);
    inputs.mi.dy = static_cast<LONG>(fy);

    // Gửi INPUT vào hệ thống
    ::SendInput(1, &inputs, sizeof(INPUT));
}
void CReceivingSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
    char lpBuf;
    int x, y;
    Receive(&lpBuf, 1);
    switch (lpBuf) {
    case 0: {
        Receive(&x, 4);
        Receive(&y, 4);
        MouseMove(x, y);
    }
          break;
    case 1: {

        LMouseDown();
    }
        break;
    case 2:
        LMouseUp();
        break;
    
    }

	CSocket::OnReceive(nErrorCode);
}