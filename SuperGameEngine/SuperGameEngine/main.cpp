#include <Windows.h>
#include <SDL.h>
// SDL_main.h is included automatically from SDL.h, so you always get the nasty #define.
#undef main 

#ifdef _DEBUG
    #include <iostream>
#endif

#include "EngineEntry/EngineEntry.h"
#include "Engine/MainEngine.h"

using namespace SuperGameEngine;

int main(int argc, char* args[])
{

#ifdef _DEBUG
    AllocConsole();
    FILE* pCout;
    FILE* pCerr;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCerr, "CONOUT$", "w", stderr);
    std::cout << "Super Game Engine Version 0.0.1 Pre-Alpha" << std::endl;
#else
    FreeConsole();
#endif

    EngineEntry engineEntry = EngineEntry();
    std::shared_ptr<Engine> engine = std::make_shared<MainEngine>();
    return engineEntry.RunApplication(engine);
}