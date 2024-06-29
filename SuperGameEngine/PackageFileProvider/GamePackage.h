#pragma once
#include <vector>
#include <string>

namespace PackageFileProvider
{
    /// <summary>
    /// Represents the files to run the game.
    /// Whether they be literal Files on disk or within a package it should not matter.
    /// </summary>
    class GamePackage
    {
    public:
        /// <summary>
        /// Get all the files as a list.
        /// This is completly unordered or at least as ordered as the library which
        /// gave the data.
        /// </summary>
        /// <returns>All files in the package. </returns>
        virtual std::vector<std::string> GetAllFiles() = 0;

        /// <summary>
        /// Detirmines if the given path exists in the files.
        /// </summary>
        /// <param name="filePath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(std::string filePath) = 0;

        /// <summary>
        /// Gets all the files in the given directory.
        /// </summary>
        /// <param name="directoryPath">Directory path to find the files for. </param>
        /// <param name="recursive">
        /// True means this will also look into all subdirectories, 
        /// False on the given directory will be looked into.
        /// </param>
        /// <returns>All the files in the directory. </returns>
        virtual std::vector<std::string> GetAllFilesInDirectory(std::string directoryPath, bool recursive = false) = 0;
    };
}