#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "PackageFileSystemDirectory.h"

namespace FatedQuestLibraries
{
    class PackageFile;
    class PackageFiles;

    /// <summary>
    /// Handles directory methods when given a game package.
    /// </summary>
    class GamePackageFileSystemDirectory : public PackageFileSystemDirectory
    {
    public:
        explicit GamePackageFileSystemDirectory(const std::shared_ptr<PackageFiles>& files);
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

        /// <summary>
        /// Refresh the files in the system.
        /// Call this after making changes to the PackageFiles.
        /// </summary>
        virtual void Refresh();

    protected:

        /// <summary>
        /// Adds the path to the given collection.
        /// </summary>
        /// <param name="collection">Collection, meaning the dictionary of dictionaries. </param>
        /// <param name="directory">The key or directory. </param>
        /// <param name="rawPath">
        /// The raw path to be processed.
        /// </param>
        /// <remark>
        /// The reason why this is protected is to allow Tools to be more explicit about how filenames are returned.
        /// </remark>
        virtual void AddPathToCollection(
            std::unordered_map<std::string, std::unordered_set<std::string>>& collection,
            const std::string& directory,
            const std::string& rawPath) const;

        /// <summary>
        /// Adds the given key and value to the collection if it does not currently exist.
        /// </summary>
        /// <param name="collection">Collection, meaning the dictionary of dictionaries. </param>
        /// <param name="key">Key to look for. </param>
        /// <param name="newValue">
        /// Value within the Dictionary value to add if it does not exist.
        /// </param>
        void AddToCollection(
            std::unordered_map<std::string, std::unordered_set<std::string>>& collection,
            const std::string& key,
            const std::string& newValue) const;

    private:

        /// <summary>
        /// All file paths currently given.
        /// </summary>
        std::unordered_map<std::string, std::unordered_set<std::string>> m_filePaths;

        /// <summary>
        /// All the files in the game package.
        /// Will be changes outside of this class.
        /// </summary>
        std::shared_ptr<PackageFiles> m_packageFiles;

        /// <summary>
        /// All directories sorted by Directory and then direct subdirectories.
        /// The key is the path from Products, the values are then the directory names directly
        /// within that folder.
        /// Empty string is valid as the top level directory.
        /// </summary>
        std::unordered_map<std::string, std::unordered_set<std::string>> m_directories;
    };
}
