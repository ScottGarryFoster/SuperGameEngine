#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class PackageFileSystemFile;
    class PackageFileSystemDirectory;

    /// <summary>
    /// Holds the content for the game.
    /// </summary>
    class GamePackage
    {
    public:
        virtual ~GamePackage() = default;

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
