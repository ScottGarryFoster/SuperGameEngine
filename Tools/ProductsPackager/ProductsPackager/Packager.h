#pragma once
#include <string>

#include "PackageFileType.h"

namespace FatedQuestLibraries
{
    class BinaryZip;
}

using namespace FatedQuestLibraries;

namespace ProductsPackager
{
    /// <summary>
    /// Packages Products.
    /// </summary>
    class Packager
    {
    public:
        Packager();
        virtual ~Packager();

        /// <summary>
        /// Packages the given directory into a package of the given directory.
        /// </summary>
        /// <param name="fullPathFrom">The location to find file. </param>
        /// <param name="fullPathTo">The location to create the end result. </param>
        /// <param name="fileType">How to treat files in the conversion. </param>
        /// <returns>True means could convert. </returns>
        bool PackageProductFolder(const std::string& fullPathFrom, const std::string& fullPathTo, PackageFileType fileType);

    private:

        std::shared_ptr<BinaryZip> m_binaryZip;
    };
}
