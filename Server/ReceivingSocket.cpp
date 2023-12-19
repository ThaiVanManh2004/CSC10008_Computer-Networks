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

void LMouseDoubleClick()
{
    // Tạo và gửi sự kiện double click
    INPUT down, up, down2;

    // Sự kiện click chuột trái
    down.type = INPUT_MOUSE;
    down.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Sự kiện nhả chuột trái
    up.type = INPUT_MOUSE;
    up.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    down2.type = INPUT_MOUSE;
    down2.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &down, sizeof(INPUT) * 1);
    SendInput(1, &up, sizeof(INPUT) * 1);
    SendInput(1, &down2, sizeof(INPUT) * 1);
}
void RMouseDown() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = cursorPos.x * (65535.0f / fScreenWidth);
    double fy = cursorPos.y * (65535.0f / fScreenHeight);

    // Tạo và cấu hình INPUT để di chuyển chuột đến tọa độ mới và bấm chuột trái
    INPUT inputs = { 0 };

    // Bấm chuột phải
    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN;
    inputs.mi.dx = static_cast<LONG>(fx);
    inputs.mi.dy = static_cast<LONG>(fy);

    // Gửi INPUT vào hệ thống
    ::SendInput(1, &inputs, sizeof(INPUT));
}
void RMouseUp() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = cursorPos.x * (65535.0f / fScreenWidth);
    double fy = cursorPos.y * (65535.0f / fScreenHeight);

    // Tạo và cấu hình INPUT để di chuyển chuột đến tọa độ mới và bấm chuột trái
    INPUT inputs = { 0 };


    // Nhả chuột phải
    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTUP;
    inputs.mi.dx = static_cast<LONG>(fx);
    inputs.mi.dy = static_cast<LONG>(fy);

    // Gửi INPUT vào hệ thống
    ::SendInput(1, &inputs, sizeof(INPUT));
}
void RMouseDoubleClick()
{
    // Tạo và gửi sự kiện double click
    INPUT down, up, down2;

    // Sự kiện click chuột trái
    down.type = INPUT_MOUSE;
    down.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    // Sự kiện nhả chuột trái
    up.type = INPUT_MOUSE;
    up.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    down2.type = INPUT_MOUSE;
    down2.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &down, sizeof(INPUT) * 1);
    SendInput(1, &up, sizeof(INPUT) * 1);
    SendInput(1, &down2, sizeof(INPUT) * 1);
}
void KeyDown(int keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = keyCode;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void KeyUp(int keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = keyCode;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void MouseWheel(short delta)
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = delta;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void CReceivingSocket::OnReceive(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    char lpBuf;
    int x, y;
    Receive(&lpBuf, 1);
    switch (lpBuf) {
    case 0:
        //tat server
    case 1:
        Receive(&x, 4);
        Receive(&y, 4);
        MouseMove(x, y);
        break;
    case 2:
        LMouseDown();
        break;
    case 3:
        LMouseUp();
        break;
    case 4:
        LMouseDoubleClick();
        break;
    case 5:
        RMouseDown();
        break;
    case 6:
        RMouseUp();
        break;
    case 7:
        RMouseDoubleClick();
    case 8: {
        int keyCode;
        Receive(&keyCode, sizeof(keyCode));
        KeyDown(keyCode);
        break;
    }
    case 9: {
        int keyCode;
        Receive(&keyCode, sizeof(keyCode));
        KeyUp(keyCode);
        break;
    }
    case 10: {
        short delta;
        Receive(&delta, sizeof(delta));
        MouseWheel(delta);
        break;
    }
    }

    CSocket::OnReceive(nErrorCode);
}
