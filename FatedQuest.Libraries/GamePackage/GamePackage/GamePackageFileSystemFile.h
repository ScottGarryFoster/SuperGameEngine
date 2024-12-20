#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "PackageFileSystemFile.h"

namespace FatedQuestLibraries
{
    class PackageFile;
    class PackageFiles;

    /// <summary>
    /// Handles file methods when given a file package.
    /// </summary>
    class GamePackageFileSystemFile : public PackageFileSystemFile
    {
    public:
        GamePackageFileSystemFile(const std::shared_ptr<PackageFiles>& files);
        virtual ~GamePackageFileSystemFile() override;

        /// <summary>
        /// Determines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filepath) const override;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual std::string ReadFileContents(const std::string& filepath) const override;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual std::vector<std::string> ReadFileContentsByLine(const std::string& filepath) const override;

        /// <summary>
        /// Refresh the files in the system.
        /// Call this after making changes to the PackageFiles.
        /// </summary>
        virtual void Refresh();

    private:

        /// <summary>
        /// All the files in the game package.
        /// Will be changes outside of this class.
        /// </summary>
        std::shared_ptr<PackageFiles> m_packageFiles;

        /// <summary>
        /// All file paths currently given.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<PackageFile>> m_filePaths;
    };
}
