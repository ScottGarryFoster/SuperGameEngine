#pragma once

#include <string>
#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Gives access to Files.
    /// </summary>
    class File
    {
    public:
        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        static bool Exists(const std::string& filepath);

        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        static bool Exists(const FString& filepath);

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        static std::string ReadFileContents(const std::string& filepath);

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        static FString ReadFileContents(const FString& filepath);

        /// <summary>
        /// Detirmines if the given path is a file.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means is filepath. False means not a filepath or a directory. </returns>
        static bool IsFile(const std::string& filepath);

        /// <summary>
        /// Delete file.
        /// </summary>
        /// <param name="filepath">Deletes the given file. </param>
        /// <returns>True means delete file. False means could not delete file or file was not a file.</returns>
        static bool Delete(const std::string& filepath);
    };
}

