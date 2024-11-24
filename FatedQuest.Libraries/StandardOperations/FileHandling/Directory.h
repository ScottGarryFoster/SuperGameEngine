#pragma once
#include <string>
#include <vector>
#include "CopyFileOptions.h"

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
    };
}