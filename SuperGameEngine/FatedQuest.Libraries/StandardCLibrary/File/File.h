#pragma once
#include "../Text/FString.h"
#include "CopyFileOptions.hpp"
#include <string>

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
        /// Detirmines if the given path is a file.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means is filepath. False means not a filepath or a directory. </returns>
        static bool IsFile(const FString& filepath);

        /// <summary>
        /// Delete file.
        /// </summary>
        /// <param name="filepath">Deletes the given file. </param>
        /// <returns>True means delete file. False means could not delete file or file was not a file.</returns>
        static bool Delete(const std::string& filepath);

        /// <summary>
        /// Delete file.
        /// </summary>
        /// <param name="filepath">Deletes the given file. </param>
        /// <returns>True means delete file. False means could not delete file or file was not a file.</returns>
        static bool Delete(const FString& filepath);

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <param name="extention">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        static bool EndInExtension(const std::string& filepath, const std::string& extention);

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <param name="extention">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        static bool EndInExtension(const FString& filepath, const FString& extention);

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <param name="extention">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        static bool EndInExtension(const FString& filepath, const std::string& extention);

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <param name="extention">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        static bool EndInExtension(const std::string& filepath, const FString& extention);

        /// <summary>
        /// Copies file to directory.
        /// </summary>
        /// <param name="inputFilepath">Filepath to copy. </param>
        /// <param name="outputDirectoryPath">Directory to copy to. </param>
        /// <param name="options">Options when copying. </param>
        /// <returns>True means copied. </returns>
        static bool CopyFile(const std::string& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options);

        /// <summary>
        /// Copies file to directory.
        /// </summary>
        /// <param name="inputFilepath">Filepath to copy. </param>
        /// <param name="outputDirectoryPath">Directory to copy to. </param>
        /// <param name="options">Options when copying. </param>
        /// <returns>True means copied. </returns>
        static bool CopyFile(const FString& inputFilepath, const FString& outputDirectoryPath, const CopyFileOptions& options);

        /// <summary>
        /// Copies file to directory.
        /// </summary>
        /// <param name="inputFilepath">Filepath to copy. </param>
        /// <param name="outputDirectoryPath">Directory to copy to. </param>
        /// <param name="options">Options when copying. </param>
        /// <returns>True means copied. </returns>
        static bool CopyFile(const std::string& inputFilepath, const FString& outputDirectoryPath, const CopyFileOptions& options);

        /// <summary>
        /// Copies file to directory.
        /// </summary>
        /// <param name="inputFilepath">Filepath to copy. </param>
        /// <param name="outputDirectoryPath">Directory to copy to. </param>
        /// <param name="options">Options when copying. </param>
        /// <returns>True means copied. </returns>
        static bool CopyFile(const FString& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options);
    };
}

