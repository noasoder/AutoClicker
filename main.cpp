#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    std::cout << "M for minecraft afk farming(left klick every 5 seconds and hold right klick)" << std::endl;
    std::cout << "P for auto click of A" << std::endl;
    std::cout << "L for left mouse with random delay between 25 and 50ms" << std::endl;
    std::cout << "0-9 for left mouse with the number n*10 as the delay in ms" << std::endl;
    std::cout << "Q to stop auto clicks" << std::endl;
    std::cout << "For new input one loop of the program is needed so you might need to hold buttons for input to register" << std::endl;
    std::cout << "ESQ to quit" << std::endl;

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    int max = 50;
    int min = 25;

    INPUT aInput;
    INPUT mouseLeftDown;
    INPUT mouseLeftUp;
    INPUT mouseRightDown;
    INPUT mouseRightUp;

    //A key
    aInput.type = INPUT_KEYBOARD;
    aInput.ki.wScan = 0;
    aInput.ki.time = 0;
    aInput.ki.dwExtraInfo = 0;
    aInput.ki.wVk = 0x41;
    aInput.ki.dwFlags = 0;

    //Left mouse
    mouseLeftDown.type = INPUT_MOUSE;
    mouseLeftDown.mi.time = 0.0f;
    mouseLeftDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    mouseLeftUp.type = INPUT_MOUSE;
    mouseLeftUp.mi.time = 0.0f;
    mouseLeftUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    //Right mouse
    mouseRightDown.type = INPUT_MOUSE;
    mouseRightDown.mi.time = 0.0f;
    mouseRightDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    mouseRightUp.type = INPUT_MOUSE;
    mouseRightUp.mi.time = 0.0f;
    mouseRightUp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    bool minecraftFarming = false;
    bool sendInput1 = false;
    bool sendInputMouse = false;
    int sendInputMouseFast = -1;
    bool isRunning = true;
    while (isRunning)
    {
        if (GetKeyState(VK_ESCAPE) & 0x8000) isRunning = false;
        //if (GetKeyState(0x53) & 0x8000) sendInput1 = true; //S Key
        if (GetKeyState(0x50) & 0x8000) sendInput1 = true; //P Key
        if (GetKeyState(0x4C) & 0x8000) sendInputMouse = true; //L Key
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
        if (GetKeyState(0x4D) & 0x8000) //M Key
        {
            SendInput(1, &mouseRightDown, sizeof(INPUT));
            minecraftFarming = true; 
        }
        if (GetKeyState(0x51) & 0x8000) //Q Key
        {
            SendInput(1, &mouseRightUp, sizeof(INPUT));
            minecraftFarming = false;
            sendInput1 = false;
            sendInputMouse = false;
            sendInputMouseFast = -1;
        }

        if (sendInput1)
        {
            SendInput(1, &aInput, sizeof(INPUT));
            sleep_for(10ms);
        }
        if (sendInputMouse)
        {
            SendInput(1, &mouseLeftDown, sizeof(INPUT));
            SendInput(1, &mouseLeftUp, sizeof(INPUT));
            int random = rand() % (max - min + 1) + min;
            sleep_for(std::chrono::milliseconds(random));
        }
        if (sendInputMouseFast > 0)
        {
            SendInput(1, &mouseLeftDown, sizeof(INPUT));
            SendInput(1, &mouseLeftUp, sizeof(INPUT));
            sleep_for(std::chrono::milliseconds(sendInputMouseFast * 10));
        }
        else if (sendInputMouseFast == 0)
        {
            SendInput(1, &mouseLeftDown, sizeof(INPUT));
            SendInput(1, &mouseLeftUp, sizeof(INPUT));
        }
        if(minecraftFarming)
        {
            SendInput(1, &mouseLeftDown, sizeof(INPUT));
            sleep_for(std::chrono::milliseconds(100));
            SendInput(1, &mouseLeftUp, sizeof(INPUT));
            sleep_for(std::chrono::milliseconds(5000));
        }
    }
    SendInput(1, &mouseRightUp, sizeof(INPUT));
}