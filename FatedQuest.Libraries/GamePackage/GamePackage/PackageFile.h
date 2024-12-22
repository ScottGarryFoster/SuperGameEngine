#pragma once
#include <string>
#include <vector>

#include "PackageFileStorageType.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A file within a game package.
    /// </summary>
    class PackageFile
    {
    public:
        virtual ~PackageFile() = default;

        /// <summary>
        /// Returns file path.
        /// </summary>
        /// <returns>File path of the file. </returns>
        virtual std::string Path() const = 0;

        /// <summary>
        /// File path with all directories split into elements of a vector.
        /// </summary>
        /// <returns>File path with all directories split into elements of a vector. </returns>
        virtual std::vector<std::string> PathByDirectory() const = 0;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::string ReadFileContents() = 0;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::vector<std::string> ReadFileContentsByLine() = 0;

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="extension">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        virtual bool EndInExtension(const std::string& extension) const = 0;

        /// <summary>
        /// Gets the filename with extension.
        /// </summary>
        /// <returns>Filename with extension. </returns>
        virtual std::string FileName() const = 0;

        /// <summary>
        /// Gets the filename extension, in this case anything after the first
        /// period counts as the extension.
        /// </summary>
        /// <returns></returns>
        virtual std::string Extension() const = 0;

        /// <summary>
        /// Gets the storage type as in whether the file format is stored
        /// as binary or is untouched from its original form.
        /// Use this to alter which method of file reading you perform.
        /// </summary>
        /// <returns>
        /// The form of the file packaged. This should help to inform you
        /// of which method to use when gathering the data back out of a package
        /// file.
        /// </returns>
        virtual PackageFileStorageType GetStorageType() const = 0;
    };
}
