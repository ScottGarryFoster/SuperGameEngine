#pragma once
#include "FileHandler.h"

namespace PackageFileProvider
{
    /// <summary>
    /// Handles file functionality using files on disk (loose files).
    /// </summary>
    class DiskFileHandler : public FileHandler
    {
    public:
        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        //virtual bool ReadFileContents(const std::string& filepath, std::string& fileOutput) = 0;

        /// <summary>
        /// Reads file contents.
        /// This version will not convert to string and returns as the output is given.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        //virtual bool ReadFileContentsUnsigned(const std::string& filepath, std::vector<unsigned char>& fileOutput) = 0;
    };
}