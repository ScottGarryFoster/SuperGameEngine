#pragma once
#include <string>
#include "ProductsPackageCompression.hpp"
#include "../../../../../SuperGameEngine/FatedQuest.Libraries/BinaryOperations/BinaryZip/BinaryZip.h"

using namespace BinaryOperations;

namespace SuperGameEnginePackager
{
    /// <summary>
    /// Packages the Products for the Game.
    /// </summary>
    class ProductsPackager : public Object
    {
    public:
        ProductsPackager();

        /// <summary>
        /// Packages Products to the location for game creation.
        /// </summary>
        /// <param name="inputDirectory">Raw products folder to package. </param>
        /// <param name="outputDirectory">Where to store the package. </param>
        /// <param name="compressionLevel">At what level to product the package. </param>
        /// <param name="error">If not packaged this contains an error as to why. </param>
        /// <returns>True means could create. </returns>
        virtual bool PackageProducts(
            std::string inputDirectory, 
            std::string outputDirectory,
            ProductsPackageCompression compressionLevel,
            std::string& error
        );
    private:
        /// <summary>
        /// Enables Zip functionality for packaging.
        /// </summary>
        std::shared_ptr<BinaryZip> m_binaryZip;
    };
}