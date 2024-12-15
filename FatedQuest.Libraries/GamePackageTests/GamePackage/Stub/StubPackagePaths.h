#pragma once
#include "../../../GamePackage/GamePackage/PackagePaths.h"

#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    class StubPackagePaths : public PackagePaths
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
        inline virtual std::string ProductsDirectory() const override
        {
            return m_productsDirectory;
        };

        std::string m_productsDirectory = std::string();
    };
}