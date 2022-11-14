#include "clicker.hpp"
#include "utils.hpp"

// credit to fsnikb (github.com/fsnikb)
//
int clicker::random::drop() {
    std::mt19937 offset{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution delay{ 60, 70 };
    if (delay(offset) == 60)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay(offset)));
        if (utils::debug::logs) { std::cout << "[+] CPS Dropped" << std::endl; }
    }

    return delay(offset);
}

int clicker::random::random_int(int min, int max) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void clicker::mouse::LDOWN()
{
    POINT p;
    GetCursorPos(&p);
    SendMessage(GetForegroundWindow(), WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(p.x, p.y));
    if (utils::debug::logs == true) { std::cout << "[+] Clicking" << std::endl; }
}

void clicker::mouse::LUP()
{
    POINT p;
    GetCursorPos(&p);
    SendMessage(GetForegroundWindow(), WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(p.x, p.y));
}

extern void clicker::thread() {
    if (utils::debug::logs == true) { std::cout << "[+] Clicker Ready! Hold down the back side mouse button!" << std::endl; }
    Sleep(500);
    if (utils::debug::logs == true) { std::cout << "[>] Welcome, " << utils::userdata::username << std::endl; }
    for (;; std::this_thread::sleep_for(std::chrono::milliseconds(1))) {
        if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000) { // side mouse button

            clicker::mouse::LDOWN();
            std::this_thread::sleep_for(std::chrono::milliseconds(clicker::random::random_int(clicker::random::mindelay, clicker::random::maxdelay)) / 1);
            clicker::mouse::LUP();
            std::this_thread::sleep_for(std::chrono::milliseconds(clicker::random::random_int(clicker::random::mindelay, clicker::random::maxdelay)) / 1);

            clicker::random::drop();
        }
    }
}
