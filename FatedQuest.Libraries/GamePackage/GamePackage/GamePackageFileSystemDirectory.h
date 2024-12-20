#pragma once
#include <memory>

#include "PackageFileSystemDirectory.h"

namespace FatedQuestLibraries
{
    class PackageFiles;

    /// <summary>
    /// Handles directory methods when given a game package.
    /// </summary>
    class GamePackageFileSystemDirectory : public PackageFileSystemDirectory
    {
    public:
        GamePackageFileSystemDirectory(const std::shared_ptr<PackageFiles>& files);
        virtual ~GamePackageFileSystemDirectory() override;

        /// <summary>
        /// Determines if a directory exists.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>True means does exist. </returns>
        virtual bool Exists(const std::string& path) const override;

        /// <summary>
        /// Lists all files in the directory.
        /// </summary>
        /// <param name="path">Path to directory. </param>
        /// <returns>
        /// A list of files or empty if either no files or directory does not exist.
        /// </returns>
        virtual std::vector<std::string> GetFiles(const std::string& path) const override;

        /// <summary>
        /// Lists directories in directory.
        /// </summary>
        /// <param name="path">Directory to list. </param>
        /// <returns>All directories in directory. </returns>
        virtual std::vector<std::string> ListDirectories(const std::string& path) const override;

        /// <summary>
        /// Lists directories in directory and returns just the names.
        /// </summary>
        /// <param name="path">Directory to list. </param>
        /// <returns>All directories in directory as names. </returns>
        virtual std::vector<std::string> ListDirectoryNames(const std::string& path) const override;
    };
}
