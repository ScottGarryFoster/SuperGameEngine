#pragma once
#include <memory>
#include <string>
#include <vector>

#include "PackageFile.h"

namespace FatedQuestLibraries
{
    class PackagePaths;

    /// <summary>
    /// A file within the game package stored raw not within a zip file.
    /// </summary>
    class PackageFilePathing : public PackageFile
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="paths">Product paths.  </param>
        /// <param name="path">Path from products location. </param>
        PackageFilePathing(std::weak_ptr<PackagePaths> paths, const std::string& path);

        /// <summary>
        /// Returns file path.
        /// </summary>
        /// <returns>File path of the file. </returns>
        virtual std::string Path() const override;

        /// <summary>
        /// File path with all directories split into elements of a vector.
        /// </summary>
        /// <returns>File path with all directories split into elements of a vector. </returns>
        virtual std::vector<std::string> PathByDirectory() const override;

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="extension">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        virtual bool EndInExtension(const std::string& extension) const override;

        /// <summary>
        /// Gets the filename with extension.
        /// </summary>
        /// <returns>Filename with extension. </returns>
        virtual std::string FileName() const override;

        /// <summary>
        /// Gets the filename extension, in this case anything after the first
        /// period counts as the extension.
        /// </summary>
        /// <returns></returns>
        virtual std::string Extension() const override;

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
        virtual PackageFileStorageType GetStorageType() const override;

    protected:
        /// <summary>
        /// File path from products folder, given at construction.
        /// </summary>
        std::string m_relativePath;

        /// <summary>
        /// Full filepath.
        /// </summary>
        std::string m_fullPath;

        /// <summary>
        /// All the directories upto where the file lives.
        /// </summary>
        std::vector<std::string> m_directories;

        /// <summary>
        /// Filename.
        /// </summary>
        std::string m_fileName;

        /// <summary>
        /// Filename Extension.
        /// </summary>
        std::string m_extension;

        /// <summary>
        /// The form of the file packaged. This should help to inform you
        /// of which method to use when gathering the data back out of a package
        /// file.
        /// </summary>
        PackageFileStorageType m_packageFileStorageType;
    };
}
