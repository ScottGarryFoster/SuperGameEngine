#pragma once
#include <string>
#include <vector>
#include "CopyFileOptions.h"

#include <filesystem>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Operations for handling directories.
    /// </summary>
    class Directory
    {
    public:
        /// <summary>
        /// Determines if a directory exists.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means does exist. </returns>
        static bool Exists(const std::string& path);

        /// <summary>
        /// Determines if path is a directory.
        /// Directory must exist.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means directory. </returns>
        static bool IsDirectory(const std::string& path);

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// This returns just the filename! Not the full path.
        /// </returns>
        static std::vector<std::string> GetFiles(const std::string& path);

        /// <summary>
        /// Creates the directory and any in between.
        /// </summary>
        /// <param name="path">
        /// Path to ensure the directories exist in.
        /// Can be a file path. </param>
        /// <returns>True means created. </returns>
        static bool CreateDirectories(const std::string& path);

        /// <summary>
        /// Remove all directories and files for the given path.
        /// </summary>
        /// <param name="path">Path to remove all for. </param>
        /// <returns>True means successful. False means something went wrong. </returns>
        static bool RemoveAll(const std::string& path);

        /// <summary>
        /// Copies a directory to another location.
        /// </summary>
        /// <param name="inputPath">Input directory. </param>
        /// <param name="outputPath">Output directory (do not include the new name). </param>
        /// <param name="options">Instructs how to copy. </param>
        /// <returns>True means sucessful. </returns>
        static bool CopyDirectory(const std::string& inputPath, const std::string& outputPath, const CopyFileOptions& options);

        /// <summary>
        /// Gets the temp directory path.
        /// </summary>
        /// <returns>
        /// The path to the temp directory on the computer or
        /// an empty string if it cannot be retrived.
        /// </returns>
        static std::string GetTempDirectory();

        /// <summary>
        /// Combines paths as strings together.
        /// </summary>
        /// <typeparam name="...FilepathAsString">Filepaths as strings.</typeparam>
        /// <param name="...args">All filepaths to combine as strings. </param>
        /// <returns>A combined file path. </returns>
        template <typename... FilepathAsString>
        static std::string CombinePath(const FilepathAsString&... args)
        {
            //static_assert((std::is_same_v<FilepathAsString, std::string> && ...),
            //    "Directory::CombinePath: All arguments must be strings.");

            std::filesystem::path combinedPath;
            (combinedPath /= ... /= args);

            return combinedPath.string();
        }

        /// <summary>
        /// Lists directories in directory.
        /// </summary>
        /// <param name="path">Directory to list. </param>
        /// <returns>All directories in directory. </returns>
        static std::vector<std::string> ListDirectories(const std::string& path);

        /// <summary>
        /// Lists directories in directory and returns just the names.
        /// </summary>
        /// <param name="path">Directory to list. </param>
        /// <returns>All directories in directory as names. </returns>
        static std::vector<std::string> ListDirectoryNames(const std::string& path);

        /// <summary>
        /// Lists files in the given directory.
        /// </summary>
        /// <param name="path">Directory to look within. </param>
        /// <returns>All files in directory as full paths. </returns>
        static std::vector<std::string> ListFiles(const std::string& path);

        /// <summary>
        /// Lists files in the given directory and returns just the filenames.
        /// </summary>
        /// <param name="path">Directory to look within. </param>
        /// <returns>All files in directory as filenames. </returns>
        static std::vector<std::string> ListFileNames(const std::string& path);

        /// <summary>
        /// Gets the parent directory of the given path.
        /// </summary>
        /// <param name="path">Path to find the parent. </param>
        /// <returns>Parent directory of the given path or string empty if there is no parent. </returns>
        static std::string GetParent(const std::string& path);
    };
}