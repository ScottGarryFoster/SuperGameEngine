#pragma once
#include "PackageContents.h"
#include "../../../FatedQuest.Libraries/BinaryOperations/BinaryZip/BinaryZip.h"

#include <string>

using namespace StandardCLibrary;
using namespace BinaryOperations;

namespace SuperGameEngine
{
    class ProductsPackage : public PackageContents
    {
    public:
        ProductsPackage();

        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filepath) override;

        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const FString& filepath) override;

        /// <summary>
        /// Detirmines if the file path exists.
        /// Will not check for binary version or non-binary version, only if the exact
        /// filepath exists in the package.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool ExplictlyExists(const std::string& filepath) override;

        /// <summary>
        /// Detirmines if the file path exists.
        /// Will not check for binary version or non-binary version, only if the exact
        /// filepath exists in the package.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool ExplictlyExists(const FString& filepath) override;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContents(const std::string& filepath, std::string& fileOutput) override;

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContents(const FString& filepath, FString& fileOutput) override;

        /// <summary>
        /// Reads file contents.
        /// This version will not convert to string and returns as the output is given.
        /// </summary>
        /// <param name="filepath">Direct file path. This should be a full file path. </param>
        /// <returns>File contents. </returns>
        virtual bool ReadFileContentsUnsigned(const std::string& filepath, std::vector<unsigned char>& fileOutput) override;
    private:
        /// <summary>
        /// The directory products are stored.
        /// </summary>
        FString m_productsDirectory;

        /// <summary>
        /// All the files in the Archive.
        /// </summary>
        std::vector<std::string> m_productArchiveFiles;

        /// <summary>
        /// Allows operations on Zip files.
        /// </summary>
        std::unique_ptr<BinaryZip> m_binaryZip;

        /// <summary>
        /// Represents a single directory.
        /// Used for searching for files by directory.
        /// </summary>
        class DirectoryInfo
        {
        public:
            /// <summary>
            /// Name of this directory.
            /// </summary>
            std::string Name = std::string();

            /// <summary>
            /// Children directories.
            /// </summary>
            std::vector<std::shared_ptr<DirectoryInfo>> ChildDirectory;
            
            /// <summary>
            /// Files within the directory.
            /// </summary>
            std::vector<std::string> Files;
        };

        /// <summary>
        /// Product archive which is ordered and sorted by the directory it is in.
        /// </summary>
        std::vector<std::shared_ptr<DirectoryInfo>> m_productArchiveAsDirectories;

        /// <summary>
        /// Loads the given file from within the Products Zip.
        /// </summary>
        /// <param name="zipName">The Zip file to find the data. </param>
        /// <param name="innerFile">The Inner File name to load the data. </param>
        /// <param name="data">The loaded data if loaded. </param>
        /// <param name="errors">Errors when loading if any. </param>
        /// <returns> True means could load. See errors if false. </returns>
        bool LoadFileFromData(
            const std::string zipName,
            const std::string innerFile,
            std::vector<unsigned char>& data,
            std::vector<FString>& errors);

        /// <summary>
        /// Loads the Product Files Archive and fills the Cache.
        /// </summary>
        void LoadArchiveFilesIntoCache();

        void AddFileToDirectories(std::string filePath);

        std::shared_ptr<DirectoryInfo> GetDirectoryInfoForPath(std::string filePath);

        bool EndInExtension(const std::string& filepath, const std::string& extention);

        bool EndInExtension(const FString& filepath, const FString& extention);

        std::string RemoveBinaryExtension(const std::string& filepath);

        /// <summary>
        /// Detirmines if the file path exists.
        /// If found the found path will be the actual existant path.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        virtual bool Exists(const std::string& filepath, std::string& foundPath);
    };
}