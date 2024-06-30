#include "File.h"
#include "Directory.h"
#include "../Object/Asserts/FileOpenException.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include "CopyOptionsFileSystemHelper.hpp"
namespace FileSystem = std::filesystem;

using namespace StandardCLibrary;

/// <summary>
/// Detirmines if the file path exists.
/// </summary>
/// <param name="filepath">File path to test. </param>
/// <returns>True means exists. </returns>
bool File::Exists(const std::string& filepath)
{
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0);
}

/// <summary>
/// Detirmines if the file path exists.
/// </summary>
/// <param name="filepath">File path to test. </param>
/// <returns>True means exists. </returns>
bool File::Exists(const FString& filepath)
{
    FString convert = filepath;
    return File::Exists(convert.AsStdString());
}

std::string StandardCLibrary::File::ReadFileContents(const std::string& filepath)
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
        std::cout << "ASSERT " << FileOpenException().GetDisplayKey() << ": [File::ReadFileContents] "
            << "File was already open: " << filepath << std::endl;
#endif
    }

    return fileContent;
}

FString File::ReadFileContents(const FString& filepath)
{
    return FString(ReadFileContents(filepath.AsStdString()));
}

bool File::IsFile(const std::string& filepath)
{
    return FileSystem::is_regular_file(filepath);
}

bool File::IsFile(const FString& filepath)
{
    return IsFile(filepath.AsStdString());
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

bool File::Delete(const FString& filepath)
{
    return Delete(filepath.AsStdString());
}

bool File::EndInExtension(const std::string& filepath, const std::string& extention)
{
    if (filepath.size() < extention.size())
    {
        return false;
    }
    
    if(filepath.compare(filepath.size() - extention.size(), extention.size(), extention) == 0)
    {
        return true;
    }
    
    return false;
}

bool File::EndInExtension(const FString& filepath, const FString& extention)
{
    return EndInExtension(filepath.AsStdString(), extention.AsStdString());
}

bool File::EndInExtension(const FString& filepath, const std::string& extention)
{
    return EndInExtension(filepath.AsStdString(), extention);
}

bool File::EndInExtension(const std::string& filepath, const FString& extention)
{
    return EndInExtension(filepath, extention.AsStdString());
}

bool File::CopyFileToDirectory(const std::string& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options)
{
    try
    {
        if (!File::Exists(inputFilepath))
        {
            return false;
        }

        std::string directoryPath = Directory::EnsurePathIsInDirectoryForm(outputDirectoryPath);
        if (!Directory::Exists(directoryPath))
        {
            return false;
        }

        FileSystem::copy_options copyOption = Convert(options);
        FileSystem::path inputPathAsPath = inputFilepath;
        FileSystem::path destinationAsPath = directoryPath + inputPathAsPath.filename().string();

        return FileSystem::copy_file(inputPathAsPath, destinationAsPath, copyOption);
    }
    catch (const std::exception)
    {
        return false;
    }

    return false;
}

bool File::CopyFileToDirectory(const FString& inputFilepath, const FString& outputDirectoryPath, const CopyFileOptions& options)
{
    return CopyFileToDirectory(inputFilepath.AsStdString(), outputDirectoryPath.AsStdString(), options);
}

bool File::CopyFileToDirectory(const std::string& inputFilepath, const FString& outputDirectoryPath, const CopyFileOptions& options)
{
    return CopyFileToDirectory(inputFilepath, outputDirectoryPath.AsStdString(), options);
}

bool File::CopyFileToDirectory(const FString& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options)
{
    return CopyFileToDirectory(inputFilepath.AsStdString(), outputDirectoryPath, options);
}

bool File::CopyFileToPath(const std::string& inputFilepath, const std::string& outputFilePath, const CopyFileOptions& options)
{
    try
    {
        if (!File::Exists(inputFilepath))
        {
            return false;
        }

        FileSystem::copy_options copyOption = Convert(options);
        FileSystem::path inputPathAsPath = inputFilepath;
        FileSystem::path destinationAsPath = outputFilePath;

        return FileSystem::copy_file(inputPathAsPath, destinationAsPath, copyOption);
    }
    catch (const std::exception)
    {
        return false;
    }

    return false;
}

bool File::CopyFileToPath(const FString& inputFilepath, const FString& outputFilePath, const CopyFileOptions& options)
{
    return CopyFileToPath(inputFilepath.AsStdString(), outputFilePath.AsStdString(), options);
}

bool File::CopyFileToPath(const std::string& inputFilepath, const FString& outputFilePath, const CopyFileOptions& options)
{
    return CopyFileToPath(inputFilepath, outputFilePath.AsStdString(), options);
}

bool File::CopyFileToPath(const FString& inputFilepath, const std::string& outputFilePath, const CopyFileOptions& options)
{
    return CopyFileToPath(inputFilepath.AsStdString(), outputFilePath, options);
}
