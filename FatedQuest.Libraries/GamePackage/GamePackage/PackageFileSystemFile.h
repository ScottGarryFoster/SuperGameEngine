#pragma once
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    class PackageFileSystemFile
    {
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

        /// <summary>
        /// Determines if the given path is a file.
        /// File must exist.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means is filepath. False means not a filepath or a directory. </returns>
        virtual bool IsFile(const std::string& filepath) const = 0;

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="filepath">Filepath to inspect. </param>
        /// <param name="extension">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        virtual bool EndInExtension(const std::string& filepath, const std::string& extension) const = 0;
    };
}
