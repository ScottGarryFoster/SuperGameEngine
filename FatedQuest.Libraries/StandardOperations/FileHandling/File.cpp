#include "File.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "CopyOptionsFileSystemHelper.h"
#include "../../Logger/AllReferences.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace FileSystem = std::filesystem;

using namespace FatedQuestLibraries;

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

#undef CopyFile
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

std::string File::Sanitize(const std::string& path)
{
    std::string returnPath = StringHelpers::ToLower(path);
    returnPath = StringHelpers::Trim(returnPath);
    returnPath = StringHelpers::ReplaceAll(returnPath,"/","\\");
    returnPath = StringHelpers::ReplaceAll(returnPath,"\\\\","\\");

    return returnPath;
}
