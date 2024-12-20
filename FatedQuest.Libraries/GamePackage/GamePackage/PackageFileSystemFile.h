#pragma once
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Handles file methods when given a file package.
    /// </summary>
    class PackageFileSystemFile
    {
    public:
        virtual ~PackageFileSystemFile() = default;

        /// <summary>
        /// Determines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filepath) const = 0;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual std::string ReadFileContents(const std::string& filepath) const = 0;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual std::vector<std::string> ReadFileContentsByLine(const std::string& filepath) const = 0;
    };
}
