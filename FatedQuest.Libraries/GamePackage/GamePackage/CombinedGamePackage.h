#pragma once
#include <memory>
#include <string>
#include <vector>

#include "GamePackage.h"

namespace FatedQuestLibraries
{
    class GamePackageFileSystem;
    class PackagePaths;
    class BinaryZip;
    class PackageFile;

    /// <summary>
    /// A game package which is a combination of a zip and raw archive.
    /// </summary>
    class CombinedGamePackage : public GamePackage
    {
    public:
        CombinedGamePackage();
        virtual ~CombinedGamePackage() override;

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
        /// Reload the Game package and refresh the files it knows about.
        /// </summary>
        /// <returns>
        /// True means could reload,
        /// false means could not - note you likely must load this package first.
        /// </returns>
        virtual bool Reload() const override;

        /// <summary>
        /// Load the Game Package as is.
        /// </summary>
        /// <param name="paths">Access to where the package is. </param>
        /// <returns>True means loaded. </returns>
        bool Load(const std::shared_ptr<PackagePaths>& paths);

    private:
        /// <summary>
        /// The last set of the paths loaded.
        /// </summary>
        std::shared_ptr<PackagePaths> m_packagePaths;

        /// <summary>
        /// Methods to zip and unzip binary files.
        /// </summary>
        std::shared_ptr<BinaryZip> m_binaryZip;

        /// <summary>
        /// Handles file and directory methods and sorting.
        /// </summary>
        std::shared_ptr<GamePackageFileSystem> m_fileSystem;

        /// <summary>
        /// Gets all files on file.
        /// </summary>
        /// <param name="productsPath">Product path. </param>
        /// <param name="currentPath">
        /// Current path (used for recursion and is the current path we are looking at)
        /// </param>
        /// <param name="files">The output list of files. </param>
        void FillListWithAllProductsFiles(
            const std::string& productsPath, 
            const std::string& currentPath, 
            std::vector<std::string>& files) const;

        /// <summary>
        /// Find all files within the packages and add them.
        /// </summary>
        /// <returns>True means could add. </returns>
        bool AddAllFiles() const;
    };

}
