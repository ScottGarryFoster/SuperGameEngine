#pragma once
#include "CopyFileOptions.hpp"
#include "../Text/FString.h"
#include "../Collection/Organised/FList.hpp"

#include <string>


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
        static bool Exists(const std::string& path);

        /// <summary>
        /// Determines if a directory exists.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means does exist. </returns>
        static bool Exists(const FString& path);

        /// <summary>
        /// Determines if path is a directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means directory. </returns>
        static bool IsDirectory(const std::string& path);

        /// <summary>
        /// Determines if path is a directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means directory. </returns>
        static bool IsDirectory(const FString& path);

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <param name="recursive">
        /// When true list all in sub-directories as well.
        /// If true the path is relative to the given.
        /// </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFiles(const std::string& path, bool recursive = false);

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <param name="recursive">
        /// When true list all in sub-directories as well.
        /// If true the path is relative to the given.
        /// </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFiles(const FString& path, bool recursive = false);

        /// <summary>
        /// Lists all files in the directory.
        /// Returns a Standard Vector with strings.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <param name="recursive">
        /// When true list all in sub-directories as well.
        /// If true the path is relative to the given.
        /// </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// </returns>
        static std::vector<std::string> GetFilesOnlyStd(const std::string& path, bool recursive = false);

        /// <summary>
        /// Lists all filepaths in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of filepaths or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFilepaths(const std::string& path);

        /// <summary>
        /// Lists all filepaths in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of filepaths or empty if either no files or directory does not exist.
        /// </returns>
        static FList<FString> GetFilepaths(const FString& path);

        /// <summary>
        /// Creates the directory and any in between.
        /// </summary>
        /// <param name="path">
        /// Path to ensure the directories exist in.
        /// Can be a file path. </param>
        /// <returns>True means created. </returns>
        static bool CreateDirectories(const std::string& path);

        /// <summary>
        /// Creates the directory and any in between.
        /// </summary>
        /// <param name="path">
        /// Path to ensure the directories exist in.
        /// Can be a file path. </param>
        /// <returns>True means created. </returns>
        static bool CreateDirectories(const FString& path);

        /// <summary>
        /// Remove all directories and files for the given path.
        /// </summary>
        /// <param name="path">Path to remove all for. </param>
        /// <returns>True means successful. False means something went wrong. </returns>
        static bool RemoveAll(const std::string& path);

        /// <summary>
        /// Remove all directories and files for the given path.
        /// </summary>
        /// <param name="path">Path to remove all for. </param>
        /// <returns>True means successful. False means something went wrong. </returns>
        static bool RemoveAll(const FString& path);

        /// <summary>
        /// Copies a directory to another location.
        /// </summary>
        /// <param name="inputPath">Input directory. </param>
        /// <param name="outputPath">Output directory (do not include the new name). </param>
        /// <param name="options">Instructs how to copy. </param>
        /// <returns>True means sucessful. </returns>
        static bool CopyDirectory(const std::string& inputPath, const std::string& outputPath, const CopyFileOptions& options);

        /// <summary>
        /// Copies a directory to another location.
        /// </summary>
        /// <param name="inputPath">Input directory. </param>
        /// <param name="outputPath">Output directory (do not include the new name). </param>
        /// <param name="options">Instructs how to copy. </param>
        /// <returns>True means sucessful. </returns>
        static bool CopyDirectory(const FString& inputPath, const FString& outputPath, const CopyFileOptions& options);

        /// <summary>
        /// Copies a directory to another location.
        /// </summary>
        /// <param name="inputPath">Input directory. </param>
        /// <param name="outputPath">Output directory (do not include the new name). </param>
        /// <param name="options">Instructs how to copy. </param>
        /// <returns>True means sucessful. </returns>
        static bool CopyDirectory(const std::string& inputPath, const FString& outputPath, const CopyFileOptions& options);

        /// <summary>
        /// Copies a directory to another location.
        /// </summary>
        /// <param name="inputPath">Input directory. </param>
        /// <param name="outputPath">Output directory (do not include the new name). </param>
        /// <param name="options">Instructs how to copy. </param>
        /// <returns>True means sucessful. </returns>
        static bool CopyDirectory(const FString& inputPath, const std::string& outputPath, const CopyFileOptions& options);

        static std::string EnsurePathIsInDirectoryForm(const std::string& inputDirectoryPath);
    };
}

