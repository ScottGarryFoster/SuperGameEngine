#include "PackageFileArchived.h"

#include <utility>

#include "PackagePaths.h"
#include "../../BinaryOperations/BinaryZip/BinaryZip.h"
#include "../../StandardOperations/FileHandling/Directory.h"

using namespace FatedQuestLibraries;

PackageFileArchived::PackageFileArchived(
    std::weak_ptr<PackagePaths> paths,
    std::shared_ptr<BinaryZip> binaryZip, 
    const std::string& path) : PackageFilePathing(paths, path)
{
    m_productsPath = {};
    if (const std::shared_ptr<PackagePaths> sharedPtr = paths.lock())
    {
        m_productsPath = sharedPtr->ProductsDirectory();
        m_zipPath = Directory::CombinePath(m_productsPath, "Products.zip");

        std::string directoryName = sharedPtr->ProductsArchiveName();
        if (directoryName.empty())
        {
            m_fullPath = Directory::CombinePath(sharedPtr->ProductsDirectory(), path);
        }
        else
        {
            m_fullPath = Directory::CombinePath(sharedPtr->ProductsDirectory(), directoryName, path);
        }
    }

    m_binaryZip = std::move(binaryZip);

}

std::string PackageFileArchived::ReadFileContents() const
{
    std::vector<unsigned char> data;
    std::vector<std::string> error;
    if (m_packageFileStorageType == PackageFileStorageType::Binary)
    {
        m_binaryZip->ExtractSingleBinaryFileToData(
            m_zipPath, m_relativePath,
            data, error);
    }
    else
    {
        m_binaryZip->ExtractSingleFileToData(
            m_zipPath, m_relativePath,
            data, error);
    }

    std::string contents(data.begin(), data.end());
    return contents;
}

std::vector<std::string> PackageFileArchived::ReadFileContentsByLine() const
{
    std::vector<unsigned char> data;
    std::vector<std::string> error;
    if (m_packageFileStorageType == PackageFileStorageType::Binary)
    {
        m_binaryZip->ExtractSingleBinaryFileToData(
            m_zipPath, m_relativePath,
            data, error);
    }
    else
    {
        m_binaryZip->ExtractSingleFileToData(
            m_zipPath, m_relativePath,
            data, error);
    }

    std::vector<std::string> result;
    std::string current_string;
    for (unsigned char ch : data)
    {
        if (ch == '\n') {
            // If newline, add the current string to the result and reset
            result.push_back(current_string);
            current_string.clear();
        }
        else {
            // Append the character to the current string
            current_string += static_cast<char>(ch);
        }
    }

    // Add the last string if it's not empty
    if (!current_string.empty()) {
        result.push_back(current_string);
    }

    return result;
}

std::vector<unsigned char> PackageFileArchived::ReadFileContentsExplicitly() const
{
    std::vector<unsigned char> data;
    std::vector<std::string> error;
    if (m_packageFileStorageType == PackageFileStorageType::Binary)
    {
        m_binaryZip->ExtractSingleBinaryFileToData(
            m_zipPath, m_relativePath,
            data, error);
    }
    else
    {
        m_binaryZip->ExtractSingleFileToData(
            m_zipPath, m_relativePath,
            data, error);
    }

    return data;
}
