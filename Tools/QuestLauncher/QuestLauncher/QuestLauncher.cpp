#include <windows.h>

#include "Window/WindowsTrayWindow.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd){

    auto window = QuestLauncher::WindowsTrayWindow(hInst, hPrevInst, lpCmdLine, nShowCmd);
    return 0;
}