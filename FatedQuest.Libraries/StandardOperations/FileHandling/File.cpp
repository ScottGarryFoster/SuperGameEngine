#include "File.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "CopyOptionsFileSystemHelper.h"

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
#ifdef _DEBUG
        // TODO: Consider throwing an exception here.
        std::cout << "EXCEPTION: " << ": [File::ReadFileContents] "
            << "File was already open: " << filepath << std::endl;
#endif
    }

    return fileContent;
}

std::vector<unsigned char> File::ReadFileContentsCharArray(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
#ifdef _DEBUG
        // TODO: Consider throwing an exception here.
        std::cout << "EXCEPTION: " << ": [File::ReadFileContentsCharArray] "
            << "File was already open: " << filepath << std::endl;
        return {};
#endif
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(fileSize);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize))
    {
#ifdef _DEBUG
        // TODO: Consider throwing an exception here.
        std::cout << "EXCEPTION: " << ": [File::ReadFileContentsCharArray] "
            << "Failed to read the file: " << filepath << std::endl;
        return {};
#endif

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

bool FatedQuestLibraries::File::CopyFile(const std::string& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options)
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
    catch (const std::exception)
    {
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
    catch (const std::exception)
    {
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
