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
    class PackageFileArchived : public PackageFilePathing
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="paths">Product paths.  </param>
        /// <param name="binaryZip">Access to Zip methods.  </param>
        /// <param name="path">Path from products location. </param>
        PackageFileArchived(std::weak_ptr<PackagePaths> paths, std::shared_ptr<BinaryZip> binaryZip, const std::string& path);

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::string ReadFileContents() override;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::vector<std::string> ReadFileContentsByLine() override;

        /// <summary>
        /// Reads file contents.
        /// This will read it explicitly, with no conversions
        /// directly into a char array (vector in this case to package the size in one
        /// object).
        /// </summary>
        /// <returns>File contents. </returns>
        /// <remarks>
        /// This is the one most likely for retail outside of mods so
        /// ensure this version is kept relatively quick.
        /// </remarks>
        virtual std::vector<unsigned char> ReadFileContentsExplicitly() override;

    private:
        /// <summary>
        /// The location the products folder is.
        /// </summary>
        std::string m_productsPath;

        /// <summary>
        /// Location of the Archive.
        /// </summary>
        std::string m_zipPath;

        /// <summary>
        /// Methods to zip and unzip binary files.
        /// </summary>
        std::shared_ptr<BinaryZip> m_binaryZip;
    };
}
