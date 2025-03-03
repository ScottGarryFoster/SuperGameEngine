#include "FilePaths.h"
#include <filesystem>
#include <iostream>

#include "Directory.h"

#if defined(_WINDOWS)
#include <windows.h>
#elif defined(_APPLE)
#include <mach-o/dyld.h>
#include <limits.h>
#elif defined(_LINUX)
#include <unistd.h>
#include <limits.h>
#endif

using namespace FatedQuestLibraries;

std::string FilePaths::ApplicationDirectory()
{
    char buffer[MAX_PATH];

#if defined(_WINDOWS)
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
#elif defined(__APPLE__)
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) != 0) {
        throw std::runtime_error("Buffer too small for executable path");
    }
#elif defined(__linux__)
    ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (length == -1) {
        throw std::runtime_error("Failed to read /proc/self/exe");
    }
    buffer[length] = '\0';
#endif

    return std::filesystem::path(buffer).parent_path().string();
}

std::string FilePaths::RepositoryDirectory()
{
    std::filesystem::path currentPath(ApplicationDirectory());
    std::string fatedQuestDirectory = Directory::CombinePath(currentPath, "FatedQuest.Libraries");
    std::string superGameEngineDirectory = Directory::CombinePath(currentPath, "SuperGameEngine");
    std::string toolsDirectory = Directory::CombinePath(currentPath, "Tools");
    for (size_t i = 0; i < 10; ++i)
    {
        // The repository directory is one which contains all three folders.
        if (Directory::Exists(fatedQuestDirectory) && 
            Directory::Exists(superGameEngineDirectory) &&
            Directory::Exists(toolsDirectory))
        {
            break;
        }

        currentPath = currentPath.parent_path();
        fatedQuestDirectory = Directory::CombinePath(currentPath, "FatedQuest.Libraries");
        superGameEngineDirectory = Directory::CombinePath(currentPath, "SuperGameEngine");
        toolsDirectory = Directory::CombinePath(currentPath, "Tools");
    }

    return currentPath.string();
}
