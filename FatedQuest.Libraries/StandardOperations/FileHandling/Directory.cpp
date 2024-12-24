#include "Directory.h"
#include <filesystem>
#include "CopyOptionsFileSystemHelper.h"
#include "../../Logger/AllReferences.h"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG
#include <cstdarg>

using namespace FatedQuestLibraries;
namespace FileSystem = std::filesystem;

bool Directory::Exists(const std::string& path)
{
    try
    {
        return FileSystem::exists(path) && FileSystem::is_directory(path);
    }
    catch (const FileSystem::filesystem_error)
    {
        // Caught but unused.
    }
    catch (const std::exception)
    {
        // Caught but unused.
    }

    return false;
}

bool Directory::IsDirectory(const std::string& path)
{
    try
    {
        return FileSystem::is_directory(path);
    }
    catch (const FileSystem::filesystem_error)
    {
        // Caught but unused.
    }
    catch (const std::exception)
    {
        // Caught but unused.
    }

    return false;
}

std::vector<std::string> Directory::GetFiles(const std::string& path)
{
    std::vector<std::string> extracted;
    try
    {
        for (const auto& filepath : FileSystem::directory_iterator(path))
        {
            if (filepath.is_regular_file())
            {
                extracted.push_back(filepath.path().filename().string());
            }
        }
    }
    catch (const FileSystem::filesystem_error)
    {
        // Caught but unused.
    }
    catch (const std::exception)
    {
        // Caught but unused.
    }

    return extracted;
}

bool Directory::CreateDirectories(const std::string& path)
{
    try
    {
        FileSystem::create_directories(path);
    }
    catch (const FileSystem::filesystem_error)
    {
        return false;
    }
    catch (const std::exception)
    {
        return false;
    }

    return true;
}

bool Directory::RemoveAll(const std::string& path)
{
    try
    {
        // Remove the directory and all its contents
        FileSystem::remove_all(path);
    }
    catch (const FileSystem::filesystem_error)
    {
        return false;
    }

    return true;
}

bool Directory::CopyDirectory(const std::string& inputPath, const std::string& outputPath, const CopyFileOptions& options)
{
    try
    {
        if (!Directory::Exists(inputPath))
        {
            return false;
        }

        if (!Directory::Exists(outputPath))
        {
            Directory::CreateDirectories(outputPath);
        }

        FileSystem::copy_options copyOption = CopyFileOptionsHelper::Convert(options);
        FileSystem::path inputPathAsPath = inputPath;
        FileSystem::path destinationAsPath = outputPath;

        for (const auto& entry : FileSystem::recursive_directory_iterator(inputPathAsPath))
        {
            const auto& path = entry.path();
            auto relativePathStr = path.lexically_relative(inputPathAsPath).string();
            FileSystem::path targetPath = destinationAsPath / relativePathStr;

            if (IsDirectory(path.string()))
            {
                Directory::CreateDirectories(targetPath.string());
            }
            else if (FileSystem::is_regular_file(path.string()))
            {
                // We have File::Copy but doing this here will reduce FS calls.
                FileSystem::copy_file(path, targetPath, copyOption);
            }
        }
    }
    catch (const std::exception e)
    {
        Log::Exception("Could not copy directory", "Directory::CopyDirectory", e.what());
        return false;
    }

    return true;
}

std::string Directory::GetTempDirectory()
{
    try
    {
        FileSystem::path temp = std::filesystem::temp_directory_path();
        return temp.string();
    }
    catch (const std::exception e)
    {
        Log::Exception("Could not get temp directory", "Directory::GetTempDirectory", e.what());
        return "";
    }
}

std::vector<std::string> Directory::ListDirectories(const std::string& path)
{
    std::vector<std::string> directories;
    try 
    {
        for (const auto& entry : FileSystem::directory_iterator(path))
        {
            if (entry.is_directory())
            {
                directories.push_back(entry.path().string());
            }
        }
    }
    catch (const FileSystem::filesystem_error&)
    {

    }

    return directories;
}

std::vector<std::string> Directory::ListDirectoryNames(const std::string& path)
{
    std::vector<std::string> directories;
    try
    {
        for (const auto& entry : FileSystem::directory_iterator(path))
        {
            if (entry.is_directory())
            {
                directories.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const FileSystem::filesystem_error&)
    {

    }

    return directories;
}

std::string Directory::GetParent(const std::string& path)
{
    try
    {
        FileSystem::path filePath(path);
        return filePath.parent_path().string();
    }
    catch (const FileSystem::filesystem_error&)
    {

    }

    return {};
}
