#include <Windows.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#undef main 

#ifdef _DEBUG
    #include <iostream>
#endif

#include "../Engine/EngineEntry/EngineEntry.h"
#include "../Engine/Engine/MainEngine.h"
#include "../Engine/DebugEngine/DebugEngine.h"

// Any external projects should define their components here:
#ifdef _TOOLS
#include "../Tools/EngineIncludes/EngineInclude.h"
#endif

using namespace SuperGameEngine;

// The logic for the engine is split amongst Engine and library projects, with games having their own components.
// The SuperGameEngine project is just an entry point for Engine. Engine contains all the logic for the Game Engine.
// There is a very good reason for this - testing!
// Try as I might, pulling in the .exe via GTest proved to either not work or become a flaky mess,
// with the two projects split apart I could add unit tests and create a more stable Engine for many of the systems
// within the GameEngine.
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
    std::shared_ptr<Engine> engine = std::make_shared<SuperEngineDebug::DebugEngine>();
    return engineEntry.RunApplication(engine);
}