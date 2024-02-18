#include "FilesAndFolders.h"
#define PLATFORM_WINDOWS

#include <string>
#include <iostream>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif // WINDOWS

#include <vector>

#include "../../../FatedQuest.Libraries/StandardCLibrary/Text/FString.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

std::string FilesAndFolders::GetExeDirectory()
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

std::string FilesAndFolders::GetWorkingDirectory()
{
// Do not have a Linux Mac version but this is not going to work there.
#ifdef PLATFORM_WINDOWS
    char path[MAX_PATH] = "";
    GetCurrentDirectoryA(MAX_PATH, path);
    std::string executablePath = path;
    std::string executableDirectory = executablePath.substr(0, executablePath.find_last_of("\\"));
    return executableDirectory;
#endif // WINDOWS
}

std::string FilesAndFolders::GetProductsFolder()
{
#ifdef PLATFORM_WINDOWS
    std::string executablePath = GetWorkingDirectory();
    FString executableDirectory = FString(executablePath);

    std::vector<FString> pathSplit = FString::Split(executableDirectory, FString("\\"));

    executableDirectory = FString("");
    for (size_t i = 0; i < pathSplit.size() - 1; ++i)
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
