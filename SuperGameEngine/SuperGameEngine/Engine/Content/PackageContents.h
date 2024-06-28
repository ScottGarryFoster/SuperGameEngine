#pragma once
#include <string>

#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// File access to the package without the need to worry about
    /// the package or binary formats.
    /// </summary>
    class PackageContents
    {
    public:
        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filepath) = 0;

        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const FString& filepath) = 0;

        /// <summary>
        /// Detirmines if the file path exists.
        /// Will not check for binary version or non-binary version, only if the exact
        /// filepath exists in the package.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool ExplictlyExists(const std::string& filepath) = 0;

        /// <summary>
        /// Detirmines if the file path exists.
        /// Will not check for binary version or non-binary version, only if the exact
        /// filepath exists in the package.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool ExplictlyExists(const FString& filepath) = 0;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContents(const std::string& filepath, std::string& fileOutput) = 0;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContents(const FString& filepath, FString& fileOutput) = 0;

        /// <summary>
        /// Reads file contents.
        /// This version will not convert to string and returns as the output is given.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContentsUnsigned(const std::string& filepath, std::vector<unsigned char>& fileOutput) = 0;
    };
}

