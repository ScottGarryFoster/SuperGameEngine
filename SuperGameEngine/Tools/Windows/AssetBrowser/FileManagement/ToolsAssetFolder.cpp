#include "ToolsAssetFolder.h"
#include "ToolsAssetFile.h"
#include "../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

ToolsAssetFolder::ToolsAssetFolder(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<TextureManager>& texture, 
    const std::string& packagePath)
{
    m_gamePackage = package;
    m_textureManager = texture;
    m_packagePath = packagePath;
    m_directoryName = File::GetFilename(packagePath);

    if (std::shared_ptr<GamePackage> gamePackage = package.lock())
    {
        std::vector<std::string> fileList = gamePackage->Directory()->GetFiles(packagePath);
        for (const std::string& fileName : fileList)
        {
            std::string extension = File::GetExtension(fileName);
            if (StringHelpers::ToLower(extension) != ".ast")
            {
                continue;
            }

            std::string assetFilePackagePath = Directory::CombinePath(packagePath, fileName);

            m_files.emplace_back(std::make_shared<ToolsAssetFile>(package, texture, assetFilePackagePath, GetWeakDistributed()));
        }

        std::vector<std::string> directoryList = gamePackage->Directory()->ListDirectories(packagePath);
        for (const std::string& directoryPath : directoryList)
        {
            m_folders.emplace_back(std::make_shared<ToolsAssetFolder>(package, texture, directoryPath));
        }
    }
}

std::vector<std::shared_ptr<AssetFile>> ToolsAssetFolder::GetContainingFiles() const
{
    return m_files;
}

std::vector<std::shared_ptr<AssetFolder>> ToolsAssetFolder::GetContainingFolders() const
{
    return m_folders;
}

std::string ToolsAssetFolder::GetDisplayName() const
{
    return m_directoryName;
}

std::string ToolsAssetFolder::GetPackagePath() const
{
    return m_packagePath;
}
