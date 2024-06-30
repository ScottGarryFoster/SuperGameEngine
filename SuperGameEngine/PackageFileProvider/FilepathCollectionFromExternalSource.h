#pragma once
#include "FilepathCollection.h"
#include <memory>

namespace PackageFileProvider
{
    /// <summary>
    /// Represents a collection of filepaths which maybe queried against.
    /// </summary>
    class FilepathCollectionFromExternalSource : public FilepathCollection
    {
    public:
        FilepathCollectionFromExternalSource(const std::vector<std::string>& paths);

        /// <summary>
        /// Get all the files as a list.
        /// This is completly unordered or at least as ordered as the library which
        /// gave the data.
        /// </summary>
        /// <returns>All files in the package. </returns>
        virtual const std::vector<std::string> GetAllFiles() const override;

        /// <summary>
        /// Detirmines if the given path exists in the files.
        /// </summary>
        /// <param name="filePath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filePath) const override;

        /// <summary>
        /// Gets all the files in the given directory.
        /// </summary>
        /// <param name="directoryPath">Directory path to find the files for. </param>
        /// <returns>All the files in the directory. </returns>
        virtual const std::vector<std::string> GetAllFilesInDirectory(const std::string& directoryPath) const override;

    private:
        /// <summary>
        /// Represents a single directory.
        /// Used for searching for files by directory.
        /// </summary>
        class DirectoryInfo
        {
        public:
            /// <summary>
            /// Name of this directory.
            /// </summary>
            std::string Name = std::string();

            /// <summary>
            /// Children directories.
            /// </summary>
            std::vector<std::shared_ptr<DirectoryInfo>> ChildDirectory;

            /// <summary>
            /// Files within the directory.
            /// </summary>
            std::vector<std::string> Files;
        };

        /// <summary>
        /// This is the top directory default name.
        /// Paths which enter this class are within Products so this name is not important
        /// beyond perhaps logging.
        /// </summary>
        const std::string m_topDirectoryName = "Products";

        /// <summary>
        /// A pure list of all filepaths in no particular order.
        /// </summary>
        std::vector<std::string> m_filepaths;

        /// <summary>
        /// Product archive which is ordered and sorted by the directory it is in.
        /// This is the top directory, Products which is the default top directory.
        /// </summary>
        std::shared_ptr<DirectoryInfo> m_filePathsAsDirectories;

        /// <summary>
        /// Add the given path to the directory tree used for searching for files.
        /// </summary>
        /// <param name="pathSplit">The file path to add already split. </param>
        /// <param name="current">
        /// Current directory to search for and add the file listing to.
        /// Start with the top directory if calling for the first time.
        /// </param>
        void AddPathToDirectoryTree(const std::vector<std::string>& pathSplit, std::shared_ptr<DirectoryInfo> current);

        /// <summary>
        /// Splits a path into the steps to make it to the filepath.
        /// </summary>
        /// <param name="path">Full filepath or directory path. </param>
        /// <returns>All the segments of the filepath. </returns>
        const std::vector<std::string> SplitPathIntoParts(const std::string& path) const;

        /// <summary>
        /// Get the directory for the given path.
        /// </summary>
        /// <param name="path">A directory path. </param>
        /// <param name="current">
        /// The current directoy searching within.
        /// Send in the top directory first.
        /// </param>
        /// <returns>The directory if found or an empty pointer if not. </returns>
        std::shared_ptr<DirectoryInfo> GetDirectory(const std::string& path, std::shared_ptr<DirectoryInfo> current) const;

        /// <summary>
        /// Get the directory for the given path.
        /// </summary>
        /// <param name="pathSplit">A directory pathsplit up. </param>
        /// <param name="current">The current directoy searching within. </param>
        /// <returns>The directory if found or an empty pointer if not. </returns>
        std::shared_ptr<DirectoryInfo> GetDirectory(const std::vector<std::string>& pathSplit, std::shared_ptr<DirectoryInfo> current) const;
    };
}