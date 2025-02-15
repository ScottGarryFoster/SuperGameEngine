#pragma once
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Handles directory methods when given a game package.
    /// </summary>
    class PackageFileSystemDirectory
    {
    public:
        virtual ~PackageFileSystemDirectory() = default;

        /// <summary>
        /// Determines if a directory exists.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means does exist. </returns>
        virtual bool Exists(const std::string& path) const = 0;

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">
        /// Path to directory.
        /// This is given as Folder\\Folder2\\Folder3
        /// You do not need a \\ on the end.
        /// </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// Returned as filenames not full paths, you need to append the directory to these!
        /// </returns>
        virtual std::vector<std::string> GetFiles(const std::string& path) const = 0;

        /// <summary>
        /// Lists directories in directory.
        /// </summary>
        /// <param name="path">Directory to list. </param>
        /// <returns>All directories in directory. </returns>
        virtual std::vector<std::string> ListDirectories(const std::string& path) const = 0;

        /// <summary>
        /// Lists directories in directory and returns just the names.
        /// </summary>
        /// <param name="path">Directory to list. </param>
        /// <returns>All directories in directory as names. </returns>
        virtual std::vector<std::string> ListDirectoryNames(const std::string& path) const = 0;
    };

}
