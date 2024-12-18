#pragma once
#include <memory>
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    class PackagePaths;
    class BinaryZip;
    class PackageFile;

    /// <summary>
    /// A game package which is a combination of a zip and raw archive.
    /// </summary>
    class CombinedGamePackage
    {
    public:
        CombinedGamePackage();
        virtual ~CombinedGamePackage();

        bool Load(std::shared_ptr<PackagePaths> paths);


    private:

        /// <summary>
        /// Methods to zip and unzip binary files.
        /// </summary>
        std::shared_ptr<BinaryZip> m_binaryZip;


        std::vector<std::shared_ptr<PackageFile>> m_systemFile;

        void FillListWithAllProductsFiles(const std::string& productsPath, const std::string& currentPath, std::vector<std::string>& files);
    };

}
