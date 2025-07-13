#pragma once
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Helper class to grab paths.
    /// </summary>
    class PackagePaths
    {
    public:
        /// <summary>
        /// Gets the full directory path the Products folder should be in.
        /// This is not the products folder itself, it is the folder it is place in,
        /// so that you can add Products.zip or Products for a folder or archive.
        /// </summary>
        /// <returns>
        /// The full path directory the products folder lives within.
        /// </returns>
        virtual std::string ProductsDirectory() const = 0;

        /// <summary>
        /// The actual name of the Products Directory if loose on file.
        /// </summary>
        /// <returns>The actual name of the Products Directory if loose on file.</returns>
        virtual std::string ProductsDirectoryName() const = 0;

        /// <summary>
        /// The actual name of the Products Archive stored in the products directory.
        /// </summary>
        /// <returns>The actual name of the Products Archive stored in the products directory.</returns>
        virtual std::string ProductsArchiveName() const = 0;
    };
}


