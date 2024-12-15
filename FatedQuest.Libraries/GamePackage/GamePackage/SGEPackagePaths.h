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
        /// <summary>
        /// Gets the directory the Products folder should be in.
        /// This is not the products folder itself, it is the folder it is place in,
        /// so that you can add Products.zip or Products for a folder or archive.
        /// </summary>
        /// <returns>
        /// The directory the products folder lives within.
        /// </returns>
        virtual std::string ProductsDirectory() const override;
    };
}


