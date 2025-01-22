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

        /// <summary>
        /// Reload the Game package and refresh the files it knows about.
        /// </summary>
        /// <returns>
        /// True means could reload,
        /// false means could not - note you likely must load this package first.
        /// </returns>
        virtual bool Reload() const = 0;
    };

}
