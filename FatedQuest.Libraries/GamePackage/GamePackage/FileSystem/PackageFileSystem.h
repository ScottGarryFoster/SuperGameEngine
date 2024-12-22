#pragma once
#include <memory>
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    class PackageFileSystemFile;
    class PackageFileSystemDirectory;

    /// <summary>
    /// File methods for files within a Game Package.
    /// </summary>
    class PackageFileSystem
    {
    public:
        virtual ~PackageFileSystem() = default;

        /// <summary>
        /// Access the file methods.
        /// </summary>
        /// <returns>File methods for files within a Game Package. </returns>
        virtual const std::shared_ptr<PackageFileSystemFile> File() const = 0;

        /// <summary>
        /// Access the directory methods.
        /// </summary>
        /// <returns>Handles directory methods when given a game package. </returns>
        virtual const std::shared_ptr<PackageFileSystemDirectory> Directory() const = 0;
    };
}
