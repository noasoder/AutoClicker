#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    std::cout << "S for auto click of A" << std::endl;
    std::cout << "M for left mouse" << std::endl;
    std::cout << "Q to stop auto clicks" << std::endl;
    std::cout << "ESQ to quit" << std::endl;

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    INPUT ip;
    INPUT mouse;

    //A key
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0x41;
    ip.ki.dwFlags = 0;

    //Left mouse
    mouse.type = INPUT_MOUSE;
    mouse.ki.wScan = 0;
    mouse.ki.time = 0;
    mouse.ki.dwExtraInfo = 0;
    mouse.ki.wVk = VK_LBUTTON;
    mouse.ki.dwFlags = 0;

    bool sendInput1 = false;
    bool sendInputMouse = false;
    bool isRunning = true;
    while (isRunning)
    {
        if (GetKeyState(VK_ESCAPE) & 0x8000) isRunning = false;
        if (GetKeyState(0x53) & 0x8000) sendInput1 = true; //S Key
        if (GetKeyState(0x4D) & 0x8000) sendInputMouse = true; //M Key
        if (GetKeyState(0x51) & 0x8000) //Q Key
        {
            sendInput1 = false;
            sendInputMouse = false;
        }

        if (sendInput1)
        {
            SendInput(1, &ip, sizeof(INPUT));
            sleep_for(10ms);
        }
        if (sendInputMouse)
        {
            SendInput(1, &mouse, sizeof(INPUT));
        }
    }
}