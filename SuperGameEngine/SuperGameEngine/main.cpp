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
#ifdef _DEBUG | _TOOLS
    Log::Initialise();
#endif

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

#ifdef _TOOLS
    // Attempt to load the tools project.
    if (auto entryEntryPtr = EngineEntryFactory::CreateEngineEntry("ToolsEngineEntry"))
    {
        std::shared_ptr<Engine> engine = std::make_shared<SuperEngineDebug::DebugEngine>();
        return entryEntryPtr->RunApplication(engine);
    }
    else
    {
#ifdef _DEBUG
        std::cout << "Could not create engine entry: " << "ToolsEngineEntry" << " Please ensure it is added to the factory \n.";
#endif
        return 1;
    }
#else
    // No need to use pointers as this is internal.
    EngineEntry engineEntry = EngineEntry();
    std::shared_ptr<Engine> engine = std::make_shared<SuperEngineDebug::DebugEngine>();
    return engineEntry.RunApplication(engine);
#endif
}