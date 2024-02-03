#include "File.h"

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