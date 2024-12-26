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
#include "../../FatedQuest.Libraries/Logger/Logger/Log.h"

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
    // Is not required but is nice to get this in early.
    Log::Initialise();

#ifdef _DEBUG
    AllocConsole();
    FILE* pCout;
    FILE* pCerr;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCerr, "CONOUT$", "w", stderr);
    std::cout << "Super Game Engine Version 0.0.3 Dev" << std::endl;
#else
    FreeConsole();
#endif

#ifdef _TOOLS
    // Attempt to load the tools project.
    if (auto entryEntryPtr = EngineEntryFactory::CreateEngineEntry("ToolsEngineEntry"))
    {
        return entryEntryPtr->RunApplication("DebugEngine");
    }
    else
    {
#ifdef _DEBUG
        std::cout << "Could not create engine entry: " << "ToolsEngineEntry" << " Please ensure it is added to the factory \n.";
#endif
        return 1;
    }
#else
    // No need to use pointers this high in the stack.
    EngineEntry engineEntry = EngineEntry();
    return engineEntry.RunApplication("DebugEngine");
#endif
}