#pragma once
#include <string>
#include <vector>
#include "FilepathCollection.h"
#include <memory>

namespace PackageFileProvider
{
    /// <summary>
    /// Handles file functionality from a single I/O or source.
    /// Used to abstract the zip contents or disk based contents from other areas of code.
    /// </summary>
    class FileHandler
    {
    public:
        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContents(const std::string& filepath, std::string& fileOutput) const = 0;

        /// <summary>
        /// Reads file contents.
        /// This version will not convert to string and returns as the output is given.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContentsUnsigned(const std::string& filepath, std::vector<unsigned char>& fileOutput) const = 0;

        /// <summary>
        /// Gets the information about the FilePaths used within the File Handler.
        /// This gives the opertunity to query what filepaths this handler uses.
        /// </summary>
        /// <returns>
        /// FilepathCollection which represents a collection of filepaths which maybe queried against.
        /// </returns>
        virtual const std::shared_ptr<const FilepathCollection> GetFilePathInfo() const = 0;
    };
}