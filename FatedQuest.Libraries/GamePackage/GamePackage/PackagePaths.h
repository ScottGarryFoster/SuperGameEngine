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
        /// Gets the directory the Products folder should be in.
        /// This is not the products folder itself, it is the folder it is place in,
        /// so that you can add Products.zip or Products for a folder or archive.
        /// </summary>
        /// <returns>
        /// The directory the products folder lives within.
        /// </returns>
        virtual std::string ProductsDirectory() const = 0;
    };
}


