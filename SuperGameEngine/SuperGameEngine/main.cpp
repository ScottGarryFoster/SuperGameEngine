#include <Windows.h>

#ifdef _DEBUG
    #include <iostream>
#endif

#include "EngineEntry/EngineEntry.h"

int main()
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

    EngineEntry engine = EngineEntry();
    return engine.RunApplication();
}