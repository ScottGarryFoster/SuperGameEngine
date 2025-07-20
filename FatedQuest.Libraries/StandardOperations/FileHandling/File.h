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
        /// Changes the extension of the given filepath.
        /// </summary>
        /// <param name="filepath">Filepath to change. </param>
        /// <param name="originalExtension">Original extension to change. </param>
        /// <param name="newExtension">New extension to replace with. </param>
        /// <returns>Filepath with the extension or the same filepath if not found. </returns>
        static std::string ChangeExtension(const std::string& filepath, const std::string& originalExtension, const std::string& newExtension);

        /// <summary>
        /// Removes all extensions from the given path.
        /// </summary>
        /// <param name="filepath">File path to remove from. </param>
        /// <returns>A file path without the extensions. </returns>
        static std::string RemoveAllExtensions(const std::string& filepath);

        /// <summary>
        /// Removes the last extension.<br/>
        /// Given: folder\\filepath.png.gz ->
        /// Returns: folder\\filepath.png<br/>
        /// Given: folder\\filepath.png ->
        /// Returns: folder\\filepath
        /// </summary>
        /// <param name="filepath">File path to remove from. </param>
        /// <returns>A file path without the last extension. </returns>
        static std::string RemoveLastExtension(const std::string& filepath);

        /// <summary>
        /// Returns the last extension<br/>
        /// Given: folder\\filepath.png.gz ->
        /// Returns: .gz<br/>
        /// Given: folder\\filepath.png ->
        /// Returns: .png<br />
        /// If there is no extension returns empty string.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <returns>The last extension of the given path. </returns>
        static std::string GetExtension(const std::string& filepath);

#undef CopyFile
        /// <summary>
        /// Copies file to directory.
        /// </summary>
        /// <param name="inputFilepath">Filepath to copy. </param>
        /// <param name="outputDirectoryPath">Directory to copy to. </param>
        /// <param name="options">Options when copying. </param>
        /// <returns>True means copied. </returns>
        static bool CopyFile(const std::string& inputFilepath, const std::string& outputDirectoryPath, const CopyFileOptions& options);
#define CopyFile

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

        /// <summary>
        /// Get the filename from a given path.
        /// </summary>
        /// <param name="path">Path to look for. </param>
        /// <returns>Filename or empty if this is not possible. </returns>
        static std::string GetFilename(const std::string& path);

        /// <summary>
        /// Creates a path which is relative of the base.
        /// This means you could send in this input:
        /// Base: folder1/folder2/
        /// Target: folder1/folder2/folder3/folder4/file.txt
        /// and get folder3/folder4/file.txt
        /// Will return empty if the target is not in the base path.
        /// </summary>
        /// <param name="base">Base path to match. </param>
        /// <param name="target">Target to make relative. </param>
        /// <returns>Target path relative to base or empty if target is not in base. </returns>
        static std::string MakeRelative(const std::string& base, const std::string& target);

        /// <summary>
        /// Returns the last modified time of the given file.
        /// Will return Unix Epoch if an error occured.
        /// </summary>
        /// <param name="fullFilepath">Full path to the file. </param>
        /// <returns>Last modified time of the file. </returns>
        static std::time_t GetLastModifiedTime(const std::string& fullFilepath);
    };
}