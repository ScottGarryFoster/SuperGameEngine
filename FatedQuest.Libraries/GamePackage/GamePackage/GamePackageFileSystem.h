#pragma once
#include "PackageFileSystem.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Package file system for a game package.
    /// </summary>
    class GamePackageFileSystem : public PackageFileSystem
    {
    public:
        GamePackageFileSystem();
        virtual ~GamePackageFileSystem();

        /// <summary>
        /// Access the file methods.
        /// </summary>
        /// <returns>File methods for files within a Game Package. </returns>
        virtual const std::shared_ptr<PackageFileSystemFile> File() const;

        /// <summary>
        /// Access the directory methods.
        /// </summary>
        /// <returns>Handles directory methods when given a game package. </returns>
        virtual const std::shared_ptr<PackageFileSystemDirectory> Directory() const;

    private:


    };
}
