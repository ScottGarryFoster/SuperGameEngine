#pragma once
#include <memory>
#include <string>
#include <vector>

#include "PackageFilePathing.h"

namespace FatedQuestLibraries
{
    class BinaryZip;
    class PackagePaths;

    /// <summary>
    /// A file within the game package stored raw not within a zip file.
    /// </summary>
    class PackageFileUnarchived : public PackageFilePathing
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="paths">Product paths.  </param>
        /// <param name="binaryZip">
        /// Binary methods, largely not used for zip in this object.
        /// </param>
        /// <param name="path">Path from products location. </param>
        PackageFileUnarchived(const std::weak_ptr<PackagePaths>& paths, const std::shared_ptr<BinaryZip>& binaryZip, const std::string& path);

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::string ReadFileContents() const override;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::vector<std::string> ReadFileContentsByLine() const override;

        /// <summary>
        /// Reads file contents.
        /// This will read it explicitly, with no conversions
        /// directly into a char array (vector in this case to package the size in one
        /// object).
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::vector<unsigned char> ReadFileContentsExplicitly() const override;

    private:
        /// <summary>
        /// Methods to zip and unzip binary files.
        /// </summary>
        std::shared_ptr<BinaryZip> m_binaryZip;
    };
}
