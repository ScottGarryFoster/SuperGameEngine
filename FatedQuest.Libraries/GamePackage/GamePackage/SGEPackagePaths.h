#pragma once
#include "PackagePaths.h"
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// SuperGameEngine's location for product path.
    /// </summary>
    class SGEPackagePaths : public PackagePaths
    {
    public:
        SGEPackagePaths();

        /// <summary>
        /// Gets the directory the Products folder should be in.
        /// This is not the products folder itself, it is the folder it is place in,
        /// so that you can add Products.zip or Products for a folder or archive.
        /// </summary>
        /// <returns>
        /// The directory the products folder lives within.
        /// </returns>
        virtual std::string ProductsDirectory() const override;

        /// <summary>
        /// The actual name of the Products Directory if loose on file.
        /// </summary>
        /// <returns>The actual name of the Products Directory if loose on file.</returns>
        virtual std::string ProductsDirectoryName() const override;

        /// <summary>
        /// The actual name of the Products Archive stored in the products directory.
        /// </summary>
        /// <returns>The actual name of the Products Archive stored in the products directory.</returns>
        virtual std::string ProductsArchiveName() const override;

    private:

        /// <summary>
        /// When looking for a products directory this is the cached last found location.
        /// </summary>
        std::string m_lastDiscoveredProductsDirectory;

        /// <summary>
        /// Finds the products directory by looking for a products folder or archive.
        /// </summary>
        /// <returns>A products directory path.</returns>
        /// <remarks>This is cached and so should be safe to call multiple times. </remarks>
        std::string FindProductsDirectory() const;
    };
}


