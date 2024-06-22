#include "Directory.h"
#include "File.h"
#include <filesystem>
#include "CopyOptionsFileSystemHelper.hpp"

using namespace StandardCLibrary;

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

bool Directory::Exists(const FString& path)
{
    return Exists(path.AsStdString());
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

bool Directory::IsDirectory(const FString& path)
{
    return IsDirectory(path.AsStdString());
}

FList<FString> Directory::GetFiles(const std::string& path)
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

FList<FString> Directory::GetFiles(const FString& path)
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

FList<FString> Directory::GetFilepaths(const std::string& path)
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

FList<FString> StandardCLibrary::Directory::GetFilepaths(const FString& path)
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

bool Directory::CreateDirectories(const FString& path)
{
    return CreateDirectories(path.AsStdString());
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

bool Directory::RemoveAll(const FString& path)
{
    return RemoveAll(path.AsStdString());
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

        FileSystem::copy_options copyOption = Convert(options);
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
            else if (File::IsFile(path.string()))
            {
                // We have File::Copy but doing this here will reduce FS calls.
                FileSystem::copy_file(path, targetPath, copyOption);
            }
        }
    }
    catch (const std::exception)
    {
        return false;
    }

    return true;
}

bool Directory::CopyDirectory(const FString& inputPath, const FString& outputPath, const CopyFileOptions& options)
{
    return CopyDirectory(inputPath.AsStdString(), outputPath.AsStdString(), options);
}

bool Directory::CopyDirectory(const std::string& inputPath, const FString& outputPath, const CopyFileOptions& options)
{
    return CopyDirectory(inputPath, outputPath.AsStdString(), options);
}

bool Directory::CopyDirectory(const FString& inputPath, const std::string& outputPath, const CopyFileOptions& options)
{
    return CopyDirectory(inputPath.AsStdString(), outputPath, options);
}
