#include "TopLevelDirectories.h"
#define PLATFORM_WINDOWS

#include <string>
#include <iostream>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif // WINDOWS

#include <vector>

#include "../../FatedQuest.Libraries/StandardCLibrary/Text/FString.h"
#include "../../FatedQuest.Libraries/Logging/Logger.h"

using namespace PackageFileProvider;
using namespace StandardCLibrary;

std::string TopLevelDirectories::GetExeDirectory()
{
    // Do not have a Linux Mac version but this is not going to work there.
#ifdef PLATFORM_WINDOWS
    char path[MAX_PATH] = "";
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string executablePath = path;
    std::string executableDirectory = executablePath.substr(0, executablePath.find_last_of("\\"));

    return executableDirectory;
#endif // WINDOWS
}

std::string TopLevelDirectories::GetWorkingDirectory()
{
    // Do not have a Linux Mac version but this is not going to work there.
#ifdef PLATFORM_WINDOWS
    char path[MAX_PATH] = "";
    GetCurrentDirectoryA(MAX_PATH, path);
    std::string executablePath = path;
    return executablePath;
#endif // WINDOWS
}

std::string TopLevelDirectories::GetProductsFolder()
{
#ifdef PLATFORM_WINDOWS
    std::string executablePath = GetWorkingDirectory();
    FString executableDirectory = FString(executablePath);

    std::vector<FString> pathSplit = FString::Split(executableDirectory, FString("\\"));

    executableDirectory = FString("");

    size_t splitCutOff = pathSplit.size();
#ifdef _DEBUG
    // Debug the products live in the top of the directory.
    splitCutOff -= 2;
#endif // _DEBUG

    for (size_t i = 0; i < splitCutOff; ++i)
    {
        if (i == 0)
        {
            executableDirectory += pathSplit[i];
        }
        else
        {
            executableDirectory += FString("\\") + pathSplit[i];
        }

    }

    executableDirectory += "\\Products";

    return executableDirectory.AsStdString();
#endif // WINDOWS
}
