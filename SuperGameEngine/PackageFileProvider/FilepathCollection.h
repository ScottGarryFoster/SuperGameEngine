#pragma once
#include <vector>
#include <string>

namespace PackageFileProvider
{
    /// <summary>
    /// Represents a collection of filepaths which maybe queried against.
    /// </summary>
    class FilepathCollection
    {
    public:
        /// <summary>
        /// Get all the files as a list.
        /// This is completly unordered or at least as ordered as the library which
        /// gave the data.
        /// </summary>
        /// <returns>All files in the package. </returns>
        virtual const std::vector<std::string> GetAllFiles() const = 0;

        /// <summary>
        /// Detirmines if the given path exists in the files.
        /// </summary>
        /// <param name="filePath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filePath) const = 0;

        /// <summary>
        /// Gets all the files in the given directory.
        /// </summary>
        /// <param name="directoryPath">Directory path to find the files for. </param>
        /// <returns>All the files in the directory. </returns>
        virtual const std::vector<std::string> GetAllFilesInDirectory(const std::string& directoryPath) const = 0;
    };
}