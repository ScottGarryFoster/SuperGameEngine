#pragma once
#include "DiskFileHandler.h"

namespace PackageFileProvider
{
    /// <summary>
    /// Handles file functionality using files on disk (loose files).
    /// Will change it's output if files change.
    /// </summary>
    class ActiveDiskFileHandler : public DiskFileHandler, public FilepathCollection, public std::enable_shared_from_this<FilepathCollection>
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="topLevelFolder">
        /// The folder location on disk of the top level directory.
        /// </param>
        ActiveDiskFileHandler(const std::string& topLevelFolder);

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContents(const std::string& filepath, std::string& fileOutput) const override;

        /// <summary>
        /// Reads file contents.
        /// This version will not convert to string and returns as the output is given.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContentsUnsigned(const std::string& filepath, std::vector<unsigned char>& fileOutput) const override;

        /// <summary>
        /// Gets the information about the FilePaths used within the File Handler.
        /// This gives the opertunity to query what filepaths this handler uses.
        /// </summary>
        /// <returns>
        /// FilepathCollection which represents a collection of filepaths which maybe queried against.
        /// </returns>
        virtual const std::shared_ptr<const FilepathCollection> GetFilePathInfo() const override;

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
        /// The top level folder path.
        /// </summary>
        std::string m_topLevelDirectory;
    };
}