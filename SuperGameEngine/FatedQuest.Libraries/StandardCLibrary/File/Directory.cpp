#include "Directory.h"
#include <filesystem>

using namespace StandardCLibrary;

namespace FileSystem = std::filesystem;
bool Directory::Exists(std::string path)
{
    try
    {
        return FileSystem::exists(path) && FileSystem::is_directory(path);
    }
    catch (const FileSystem::filesystem_error e)
    {
        // Caught but unused.
    }
    catch (const std::exception e)
    {
        // Caught but unused.
    }

    return false;
}

bool Directory::Exists(FString path)
{
    std::string sPath = path.AsStdString();
    try
    {
        return FileSystem::exists(sPath) && FileSystem::is_directory(sPath);
    }
    catch (const FileSystem::filesystem_error e)
    {
        // Caught but unused.
    }
    catch (const std::exception e)
    {
        // Caught but unused.
    }

    return false;
}

FList<FString> Directory::GetFiles(std::string path)
{
    FList<FString> extracted;
    try
    {
        for (const auto& filepath : FileSystem::directory_iterator(path))
        {
            if (filepath.is_regular_file())
            {
                extracted.Add(FString(filepath.path().filename().string()));
            }
        }
    }
    catch (const FileSystem::filesystem_error e)
    {
        // Caught but unused.
    }
    catch (const std::exception e)
    {
        // Caught but unused.
    }

    return extracted;
}

FList<FString> Directory::GetFiles(FString path)
{
    std::string sPath = path.AsStdString();
    FList<FString> extracted;
    try
    {
        for (const auto& filepath : FileSystem::directory_iterator(sPath))
        {
            if (filepath.is_regular_file())
            {
                extracted.Add(FString(filepath.path().filename().string()));
            }
        }
    }
    catch (const FileSystem::filesystem_error e)
    {
        // Caught but unused.
    }
    catch (const std::exception e)
    {
        // Caught but unused.
    }

    return extracted;
}

FList<FString> Directory::GetFilepaths(std::string path)
{
    FList<FString> extracted;
    try
    {
        for (const auto& filepath : FileSystem::directory_iterator(path))
        {
            if (filepath.is_regular_file())
            {
                extracted.Add(FString(filepath.path().string()));
            }
        }
    }
    catch (const FileSystem::filesystem_error e)
    {
        // Caught but unused.
    }
    catch (const std::exception e)
    {
        // Caught but unused.
    }

    return extracted;
}

FList<FString> StandardCLibrary::Directory::GetFilepaths(FString path)
{
    std::string sPath = path.AsStdString();
    FList<FString> extracted;
    try
    {
        for (const auto& filepath : FileSystem::directory_iterator(sPath))
        {
            if (filepath.is_regular_file())
            {
                extracted.Add(FString(filepath.path().string()));
            }
        }
    }
    catch (const FileSystem::filesystem_error e)
    {
        // Caught but unused.
    }
    catch (const std::exception e)
    {
        // Caught but unused.
    }

    return extracted;
}
