#pragma once
#include <string>
#include "CopyFileOptions.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Provides File access and helper methods.
    /// </summary>
    class File
    {
    public:
        /// <summary>
        /// Determines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        static bool Exists(const std::string& filepath);

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        static std::string ReadFileContents(const std::string& filepath);

        /// <summary>
        /// Reads file contents.
        /// This will read it explicitly, with no conversions
        /// directly into a char array (vector in this case to package the size in one
        /// object).
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        static std::vector<unsigned char> ReadFileContentsCharArray(const std::string& filepath);

        /// <summary>
        /// Determines if the given path is a file.
        /// File must exist.
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

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <param name="extension">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        static bool EndInExtension(const std::string& filepath, const std::string& extension);

        /// <summary>
        /// Copies file to directory.
        /// </summary>
        /// <param name="inputFilepath">Filepath to copy. </param>
        /// <param name="outputDirectoryPath">Directory to copy to. </param>
        /// <param name="options">Options when copying. </param>
        /// <returns>True means copied. </returns>
        static bool CopyFile(const std::string& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options);

        /// <summary>
        /// Writes the line into the file.
        /// Will override any existing contents.
        /// </summary>
        /// <param name="filepath">Path to write. </param>
        /// <param name="contents">Contents to write in file. </param>
        /// <returns>True means could write. </returns>
        static bool WriteLine(const std::string& filepath, const std::string& contents);

        /// <summary>
        /// What separates file paths.
        /// </summary>
        /// <returns>The separator with file paths. </returns>
        static std::string Separator();

        /// <summary>
        /// Sanitize the path such that it should be comparable to another.
        /// </summary>
        /// <param name="path">Path to sanitize. </param>
        /// <returns>New path. </returns>
        static std::string Sanitize(const std::string& path);
    };
}