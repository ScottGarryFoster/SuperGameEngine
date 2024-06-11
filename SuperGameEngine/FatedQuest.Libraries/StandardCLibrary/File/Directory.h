#pragma once
#include <string>
#include "../Text/FString.h"
#include "../Collection/Organised/FList.hpp"

namespace StandardCLibrary
{
    /// <summary>
    /// Gives file and directory access.
    /// </summary>
    class Directory
    {
    public:

        /// <summary>
        /// Determines if a directory exists.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means does exist. </returns>
        static bool Exists(std::string path);

        /// <summary>
        /// Determines if a directory exists.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means does exist. </returns>
        static bool Exists(FString path);

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFiles(std::string path);

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFiles(FString path);

        /// <summary>
        /// Lists all filepaths in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of filepaths or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFilepaths(std::string path);

        /// <summary>
        /// Lists all filepaths in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of filepaths or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFilepaths(FString path);

        /// <summary>
        /// Creates the directory and any in between.
        /// </summary>
        /// <param name="path">
        /// Path to ensure the directories exist in.
        /// Can be a file path. </param>
        /// <returns>True means created. </returns>
        static bool CreateDirectories(std::string path);

        /// <summary>
        /// Remove all directories and files for the given path.
        /// </summary>
        /// <param name="path">Path to remove all for. </param>
        /// <returns>True means successful. False means something went wrong. </returns>
        static bool RemoveAll(std::string path);
    };
}

