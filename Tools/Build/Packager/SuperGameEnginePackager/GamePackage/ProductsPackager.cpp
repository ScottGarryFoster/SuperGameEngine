#include "ProductsPackager.h"
#include "../../../../../SuperGameEngine/FatedQuest.Libraries/BinaryOperations/BinaryZip/StandardBinaryZip.h"
#include "../../../../../SuperGameEngine/FatedQuest.Libraries/StandardCLibrary/File/CopyFileOptions.hpp"

using namespace SuperGameEnginePackager;
using namespace StandardCLibrary;

ProductsPackager::ProductsPackager()
{
    m_binaryZip = std::make_shared<StandardBinaryZip>();
}

bool ProductsPackager::PackageProducts(
    std::string inputDirectory, 
    std::string outputDirectory, 
    ProductsPackageCompression compressionLevel, 
    std::string& error
)
{
    if (inputDirectory.empty() || !Directory::Exists(inputDirectory))
    {
        error = "Input directory not found or does not exist";
        return false;
    }

    if (outputDirectory.empty() || !Directory::Exists(outputDirectory))
    {
        error = "Output directory not found or does not exist";
        return false;
    }

    std::string outputDirectoryAdjusted = outputDirectory + "\\Products";
    std::vector<std::string> errors;
    bool created = false;
    switch (compressionLevel)
    {
        case ProductsPackageCompression::Uncompressed:
            created = Directory::CopyDirectory(
                inputDirectory, 
                outputDirectoryAdjusted, 
                CopyFileOptions::RecursiveDirectories | CopyFileOptions::UpdateExistingFile);
            if(!created)
            {
                error = "Could not copy directory";
            }
            break;
        case ProductsPackageCompression::UncompressedBinary:
            created = m_binaryZip->DirectoryToBinary(inputDirectory, outputDirectoryAdjusted, errors);
            if (!created)
            {
                error = StringHelpers::Join("\n", errors);
            }
            break;
        case ProductsPackageCompression::Archive:
            created = m_binaryZip->DirectoryToZip(inputDirectory, outputDirectoryAdjusted, errors);
            if(!created)
            {
                error = StringHelpers::Join("\n", errors);
            }
            break;
        case ProductsPackageCompression::BinaryArchive:
            created = m_binaryZip->DirectoryToZipWithFileToBinary(inputDirectory, outputDirectoryAdjusted, errors);
            if (!created)
            {
                error = StringHelpers::Join("\n", errors);
            }
            break;
    }

    return created;
}
