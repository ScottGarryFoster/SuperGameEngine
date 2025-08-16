#include "File.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <filesystem>
#include "CopyOptionsFileSystemHelper.h"
#include "../../Logger/AllReferences.h"

namespace FileSystem = std::filesystem;

using namespace FatedQuestLibraries;
#undef CopyFile

bool File::Exists(const std::string& filepath)
{
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0);
}

std::string File::ReadFileContents(const std::string& filepath)
{
    std::string fileContent = "";
    std::ifstream file(filepath);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();

        // Close the file
        file.close();

        fileContent = buffer.str();
    }
    else
    {
        Log::Error("File was already open: " + filepath, "File::ReadFileContents");
        return {};
    }

    return fileContent;
}

std::vector<unsigned char> File::ReadFileContentsCharArray(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        Log::Error("File was already open: " + filepath, "File::ReadFileContentsCharArray");
        return {};
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(fileSize);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize))
    {
        Log::Error("Failed to read the file: " + filepath, "File::ReadFileContentsCharArray");
        return {};
    }

    return buffer;
}

bool File::IsFile(const std::string& filepath)
{
    return FileSystem::is_regular_file(filepath);
}

bool File::Delete(const std::string& filepath)
{
    if (!File::Exists(filepath))
    {
        return false;
    }

    if (!File::IsFile(filepath))
    {
        return false;
    }

    return FileSystem::remove(filepath);
}

bool File::EndInExtension(const std::string& filepath, const std::string& extension)
{
    if (filepath.size() < extension.size())
    {
        return false;
    }

    if (filepath.compare(filepath.size() - extension.size(), extension.size(), extension) == 0)
    {
        return true;
    }

    return false;
}

std::string File::ChangeExtension(
    const std::string& filepath, 
    const std::string& originalExtension,
    const std::string& newExtension)
{
    // In case sent in is nonsense.
    if (!EndInExtension(filepath, originalExtension))
    {
        return filepath;
    }

    std::string newFilepath = filepath.substr(0, filepath.length() - originalExtension.length());
    newFilepath += newExtension;

    return newFilepath;
}

std::string File::RemoveAllExtensions(const std::string& filepath)
{
    if (filepath.empty())
    {
        return {};
    }

    FileSystem::path input(filepath);
    while (!input.extension().empty())
    {
        input.replace_extension();
    }

    return input.string();
}

std::string File::RemoveLastExtension(const std::string& filepath)
{
    if (filepath.empty())
    {
        return {};
    }

    FileSystem::path input(filepath);
    if (!input.extension().empty())
    {
        input.replace_extension();
    }

    return input.string();
}

std::string File::GetExtension(const std::string& filepath)
{
    if (filepath.empty())
    {
        return {};
    }

    FileSystem::path input(filepath);
    return input.extension().string();
}

bool File::CopyFile(const std::string& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options)
{
    try
    {
        if (!File::Exists(inputFilepath))
        {
            return false;
        }

        FileSystem::copy_options copyOption = CopyFileOptionsHelper::Convert(options);
        FileSystem::path inputPathAsPath = inputFilepath;
        FileSystem::path destinationAsPath = outputDirectoryPath;

        return FileSystem::copy_file(inputPathAsPath, destinationAsPath, copyOption);
    }
    catch (const std::exception e)
    {
        Log::Exception("Failed to copy file: " + inputFilepath + " to " + outputDirectoryPath, "File::CopyFile", e.what());
        return false;
    }

    return false;
}

bool File::WriteLine(const std::string& filepath, const std::string& contents)
{
    try
    {
        FileSystem::path asPath(filepath);
        if (!FileSystem::exists(asPath.parent_path()))
        {
            // If the directory the path sits within does not exist - make it!
            FileSystem::create_directories(asPath.parent_path());
        }

        std::ofstream outFile(filepath, std::ios::out | std::ios::trunc);
        outFile << contents;
        outFile.close();
    }
    catch (const std::exception e)
    {
        Log::Exception("Failed to WriteLine: " + filepath, "File::WriteLine", e.what());
        return false;
    }

    return true;
}

std::string File::Separator()
{
    return "\\";
}

std::string File::Sanitize(const std::string& path, CaseRespective caseRespective)
{
    std::string returnPath = StringHelpers::Trim(path);
    returnPath = StringHelpers::ReplaceAll(returnPath,"/","\\");
    returnPath = StringHelpers::ReplaceAll(returnPath,"\\\\","\\");

    if (caseRespective == CaseRespective::AlterCaseAsNeeded)
    {
        returnPath = StringHelpers::ToLower(returnPath);
    }

    return returnPath;
}

std::string File::GetFilename(const std::string& path)
{
    try
    {
        FileSystem::path asPath(path);
        return asPath.filename().string();
    }
    catch (const std::exception& e)
    {
        Log::Exception("Path did not have a filename " + path, "File::GetFilename", e.what());
        return {};
    }
}

std::string File::MakeRelative(const std::string& base, const std::string& target)
{
    FileSystem::path absBasePath = FileSystem::absolute(base);
    FileSystem::path absTargetPath = FileSystem::absolute(target);

    // Is target within base?
    if (!equivalent(absBasePath, absBasePath.root_path()) &&
        !relative(absTargetPath, absBasePath).empty())
    {
        return relative(absTargetPath, absBasePath).string();
    }

    return {};
}

std::time_t File::GetLastModifiedTime(const std::string& fullFilepath)
{
    std::time_t returnTime = 0;
    if (!File::Exists(fullFilepath))
    {
        return returnTime;
    }

    std::error_code errorCode;
    auto fileTime = FileSystem::last_write_time(fullFilepath, errorCode);
    if (errorCode)
    {
        Log::Error("Could not get the last modified time from file. Error: " + errorCode.message(), 
            "GetLastModifiedTime(const std::string&)");
        return returnTime;
    }

    // We need this in a universal format as outside the File class,
    // the filesystem itself should be hidden away.
    auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
    return std::chrono::system_clock::to_time_t(systemTime);
}

#define CopyFile
