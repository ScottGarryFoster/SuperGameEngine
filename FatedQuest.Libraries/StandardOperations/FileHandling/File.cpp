#include "File.h"
#include <fstream>
#include <sstream>
#include <filesystem>

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

bool File::EndInExtension(const std::string& filepath, const std::string& extention)
{
    if (filepath.size() < extention.size())
    {
        return false;
    }

    if (filepath.compare(filepath.size() - extention.size(), extention.size(), extention) == 0)
    {
        return true;
    }

    return false;
}
