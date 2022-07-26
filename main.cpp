#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    std::cout << "S for auto click of A" << std::endl;
    std::cout << "M for left mouse with random delay between 25 and 50ms" << std::endl;
    std::cout << "0-9 for left mouse with the number n*10 as the delay in ms" << std::endl;
    std::cout << "Q to stop auto clicks" << std::endl;
    std::cout << "ESQ to quit" << std::endl;

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    int max = 50;
    int min = 25;

    INPUT ip;
    INPUT mouse;
    INPUT mouse2;

    //A key
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0x41;
    ip.ki.dwFlags = 0;

    //Left mouse
    mouse.type = INPUT_MOUSE;
    mouse.mi.time = 0.0f;
    mouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    mouse2.type = INPUT_MOUSE;
    mouse2.mi.time = 0.0f;
    mouse2.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    bool sendInput1 = false;
    bool sendInputMouse = false;
    int sendInputMouseFast = -1;
    bool isRunning = true;
    while (isRunning)
    {
        if (GetKeyState(VK_ESCAPE) & 0x8000) isRunning = false;
        if (GetKeyState(0x53) & 0x8000) sendInput1 = true; //S Key
        if (GetKeyState(0x4D) & 0x8000) sendInputMouse = true; //M Key
        if (GetKeyState(0x30) & 0x8000) sendInputMouseFast = 0; //0 Key
        if (GetKeyState(0x31) & 0x8000) sendInputMouseFast = 1; //1 Key
        if (GetKeyState(0x32) & 0x8000) sendInputMouseFast = 2; //2 Key
        if (GetKeyState(0x33) & 0x8000) sendInputMouseFast = 3; //3 Key
        if (GetKeyState(0x34) & 0x8000) sendInputMouseFast = 4; //4 Key
        if (GetKeyState(0x35) & 0x8000) sendInputMouseFast = 5; //5 Key
        if (GetKeyState(0x36) & 0x8000) sendInputMouseFast = 6; //6 Key
        if (GetKeyState(0x37) & 0x8000) sendInputMouseFast = 7; //7 Key
        if (GetKeyState(0x38) & 0x8000) sendInputMouseFast = 8; //8 Key
        if (GetKeyState(0x39) & 0x8000) sendInputMouseFast = 9; //9 Key
        if (GetKeyState(0x51) & 0x8000) //Q Key
        {
            sendInput1 = false;
            sendInputMouse = false;
            sendInputMouseFast = -1;
        }

        if (sendInput1)
        {
            SendInput(1, &ip, sizeof(INPUT));
            sleep_for(10ms);
        }
        if (sendInputMouse)
        {
            SendInput(1, &mouse, sizeof(INPUT));
            SendInput(1, &mouse2, sizeof(INPUT));
            int random = rand() % (max - min + 1) + min;
            sleep_for(std::chrono::milliseconds(random));
        }
        if (sendInputMouseFast > 0)
        {
            SendInput(1, &mouse, sizeof(INPUT));
            SendInput(1, &mouse2, sizeof(INPUT));
            sleep_for(std::chrono::milliseconds(sendInputMouseFast * 10));
        }
        else if (sendInputMouseFast == 0)
        {
            SendInput(1, &mouse, sizeof(INPUT));
            SendInput(1, &mouse2, sizeof(INPUT));
        }
    }
}