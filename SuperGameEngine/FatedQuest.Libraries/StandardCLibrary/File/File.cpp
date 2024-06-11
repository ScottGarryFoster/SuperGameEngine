#include "File.h"
#include "../Object/Asserts/FileOpenException.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
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
