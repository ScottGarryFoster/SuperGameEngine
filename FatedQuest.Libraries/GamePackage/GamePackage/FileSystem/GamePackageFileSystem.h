#pragma once
#include "PackageFileSystem.h"
#include <memory>
#include <unordered_map>

#include "PackageFileOrigin.h"

namespace FatedQuestLibraries
{
    class GamePackageFileSystemDirectory;
    class GamePackageFileSystemFile;
    class PackageFiles;
    class PackageFile;

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
        virtual const std::shared_ptr<PackageFileSystemFile> File() const override;

        /// <summary>
        /// Access the directory methods.
        /// </summary>
        /// <returns>Handles directory methods when given a game package. </returns>
        virtual const std::shared_ptr<PackageFileSystemDirectory> Directory() const override;

        /// <summary>
        /// Gives the file system some files from the game package.
        /// Only files it is given will be considered within the game package.
        /// </summary>
        /// <param name="packageFiles">
        /// All the package files to give.
        /// Sorted by the Origin meaning how the files are stored on disk (their origin) and then
        /// the actual files themselves in a form we can access and read without the details of how
        /// the reading will be performed.
        /// </param>
        /// <remarks>
        /// You should ideally call this once upon a game package change such as a load and
        /// perhaps a change like loading a mod.
        /// You do not want to call this continually as each time it is called, sorting and
        /// management is called to ensure the file systems are kept up to date.
        /// Keep these calls to a minimum of the required number of times.
        /// </remarks>
        virtual void GiveFiles(const std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>>& packageFiles);

    private:
        /// <summary>
        /// Handles file methods;
        /// </summary>
        std::shared_ptr<GamePackageFileSystemFile> m_fileSystem;

        /// <summary>
        /// Handles directory methods.
        /// </summary>
        std::shared_ptr<GamePackageFileSystemDirectory> m_directorySystem;

        /// <summary>
        /// All archived files we know about.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<PackageFile>> m_archivedFiles;

        /// <summary>
        /// All unarchived files we know about.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<PackageFile>> m_unarchivedFiles;

        /// <summary>
        /// All files the file and directory systems know about.
        /// Note these are files not directories.
        /// </summary>
        std::shared_ptr<PackageFiles> m_packageFiles;

        /// <summary>
        /// Called everytime a significant change occurs to files
        /// to cause a re-organisation to the files within the package.
        /// </summary>
        void Refresh();

        /// <summary>
        /// Adds a file to the given collection.
        /// </summary>
        /// <param name="collection">Collection to add to. </param>
        /// <param name="potentialNewEntry">Entry to attempt to add. </param>
        void AddToCollection(
            std::unordered_map<std::string, std::shared_ptr<PackageFile>>& collection, 
            const std::shared_ptr<PackageFile>& potentialNewEntry) const;
    };
}
