#include "ProductsPackage.h"
#include "../../../FatedQuest.Libraries/BinaryOperations/BinaryZip/StandardBinaryZip.h"
#include "../../Engine/Basic/FilesAndFolders.h"

using namespace SuperGameEngine;

ProductsPackage::ProductsPackage()
{
    m_binaryZip = std::make_unique<StandardBinaryZip>();

    m_productsDirectory = FString(FilesAndFolders::GetProductsFolder());
    LoadArchiveFilesIntoCache();
}

bool ProductsPackage::Exists(const std::string& filepath)
{
    std::string adjustedName = filepath;
    std::replace(adjustedName.begin(), adjustedName.end(), '\\', '/');
    bool givenExists = VectorHelpers::ContainsString(m_productArchiveFiles, adjustedName);
    if (!givenExists)
    {
        if (EndInExtension(adjustedName, ".gz"))
        {
            return VectorHelpers::ContainsString(
                m_productArchiveFiles, RemoveBinaryExtension(adjustedName));
        }
        else
        {
            return VectorHelpers::ContainsString(
                m_productArchiveFiles, adjustedName + ".gz");
        }
    }

    return givenExists;
}

bool ProductsPackage::Exists(const FString& filepath)
{
    return Exists(filepath.AsStdString());
}

bool ProductsPackage::ExplictlyExists(const std::string& filepath)
{
    std::string adjustedName = filepath;
    std::replace(adjustedName.begin(), adjustedName.end(), '\\', '/');
    return VectorHelpers::ContainsString(m_productArchiveFiles, adjustedName);
}

bool ProductsPackage::ExplictlyExists(const FString& filepath)
{
    return ExplictlyExists(filepath.AsStdString());
}

bool ProductsPackage::ReadFileContents(const std::string& filepath, std::string& fileOutput)
{
    fileOutput = std::string();
    std::string foundPath = std::string();
    if (!Exists(filepath, foundPath))
    {
        // Not found
        return false;
    }

    std::vector<FString> errors = std::vector<FString>();
    std::string zipName = m_productsDirectory.AsStdString() + ".zip";
    std::vector<unsigned char> outputData = std::vector<unsigned char>();
    bool loaded = LoadFileFromData(zipName, foundPath, outputData, errors);
    if (loaded)
    {
        fileOutput = StringHelpers::ConvertFrom(outputData);
    }
    else
    {
        // Consider logging errors here.
    }

    return loaded;
}

bool ProductsPackage::ReadFileContents(const FString& filepath, FString& fileOutput)
{
    fileOutput = FString();
    std::string foundPath = std::string();
    if (!Exists(filepath.AsStdString(), foundPath))
    {
        // Not found
        return false;
    }

    std::vector<FString> errors = std::vector<FString>();
    std::string zipName = m_productsDirectory.AsStdString() + ".zip";
    std::vector<unsigned char> outputData = std::vector<unsigned char>();
    bool loaded = LoadFileFromData(zipName, foundPath, outputData, errors);
    if (loaded)
    {
        fileOutput = FString(outputData);
    }
    else
    {
        // Consider logging errors here.
    }

    return loaded;
}

bool SuperGameEngine::ProductsPackage::ReadFileContentsUnsigned
    (const std::string& filepath, std::vector<unsigned char>& fileOutput)
{
    fileOutput = std::vector<unsigned char>();
    if (!Exists(filepath) && Exists(filepath + ".gz"))
    {
        // Not found
        return false;
    }

    std::vector<FString> errors = std::vector<FString>();
    std::string zipName = m_productsDirectory.AsStdString() + ".zip";
    std::vector<unsigned char> outputData = std::vector<unsigned char>();
    bool loaded = LoadFileFromData(zipName, filepath, fileOutput, errors);
    if(!loaded)
    {
        // Consider logging errors here.
        fileOutput = std::vector<unsigned char>();
    }

    return loaded;
}

bool ProductsPackage::LoadFileFromData(const std::string zipName, const std::string innerFile, std::vector<unsigned char>& data, std::vector<FString>& errors)
{
    std::vector<std::string> errorsAsString = std::vector<std::string>();

    bool created = false;
    if (File::EndInExtension(innerFile, ".gz"))
    {
        created = m_binaryZip->ExtractSingleBinaryFileToData(zipName, innerFile, data, errorsAsString);
    }
    else
    {
        created = m_binaryZip->ExtractSingleFileToData(zipName, innerFile, data, errorsAsString);
    }

    for (std::string error : errorsAsString)
    {
        errors.push_back(FString(error));
    }

    return created;
}

void ProductsPackage::LoadArchiveFilesIntoCache()
{
    std::vector<std::string> loadingZipErrors;
    m_productArchiveFiles = m_binaryZip->ListFilesInArchive(m_productsDirectory.AsStdString() + ".zip", loadingZipErrors);
    for (std::string error : loadingZipErrors)
    {
        Logger::Error("Loading Products Zip error: " + error);
    }

    // Standardise all paths in lookup to forward slashes.
    for (std::string& path : m_productArchiveFiles)
    {
        std::replace(path.begin(), path.end(), '\\', '/');
        AddFileToDirectories(path);
    }
}

void ProductsPackage::AddFileToDirectories(std::string filePath)
{

}

std::shared_ptr<ProductsPackage::DirectoryInfo> ProductsPackage::GetDirectoryInfoForPath(std::string filePath)
{
    std::vector<std::string> pathPieces = StringHelpers::Split("/", filePath);
    
    std::shared_ptr<DirectoryInfo> closestDirectory;

    bool isTopDirectory = true;
    for (const std::string& piece : pathPieces)
    {
        if (isTopDirectory)
        {
            for (const std::shared_ptr<DirectoryInfo> info: m_productArchiveAsDirectories)
            {
                if (StringHelpers::Equals(info->Name, piece, true))
                {

                }
            }
        }
    }

    return std::shared_ptr<DirectoryInfo>();
}

bool ProductsPackage::EndInExtension(const std::string& filepath, const std::string& extention)
{
    if (filepath.size() < extention.size())
    {
        return false;
    }

    if (filepath.compare(filepath.size() - extention.size(), extention.size(), extention) == 0)
    {
        return true;
    }

    return false;
}

bool ProductsPackage::EndInExtension(const FString& filepath, const FString& extention)
{
    return EndInExtension(filepath.AsStdString(), extention.AsStdString());
}

std::string ProductsPackage::RemoveBinaryExtension(const std::string& filepath)
{
    std::string removeExtension = filepath;
    if (!EndInExtension(removeExtension, ".gz"))
    {
        return removeExtension;
    }

    if (filepath.length() > 3)
    {
        size_t length = filepath.length();
        length -= 3;
        std::string removeExtension = filepath.substr(0, length);
    }

    return removeExtension;
}

bool ProductsPackage::Exists(const std::string& filepath, std::string& foundPath)
{
    foundPath = std::string();
    std::string adjustedName = filepath;
    std::replace(adjustedName.begin(), adjustedName.end(), '\\', '/');
    bool givenExists = VectorHelpers::ContainsString(m_productArchiveFiles, adjustedName);
    if (givenExists)
    {
        foundPath = adjustedName;
    }
    else
    {
        if (EndInExtension(adjustedName, ".gz"))
        {
            std::string removeBinaryExtension = RemoveBinaryExtension(adjustedName);
            givenExists = VectorHelpers::ContainsString(m_productArchiveFiles, removeBinaryExtension);
            if(givenExists)
            {
                foundPath = removeBinaryExtension;
            }
        }
        else
        {
            std::string binaryExtension = adjustedName + ".gz";
            givenExists = VectorHelpers::ContainsString(m_productArchiveFiles, binaryExtension);
            if (givenExists)
            {
                foundPath = binaryExtension;
            }
        }
    }

    return givenExists;
}
