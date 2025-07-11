#include "ToolsAssetFileProvider.h"
#include "../../../FatedQuestLibraries.h"

#include <string>

#include "ToolsAssetFolder.h"

using namespace SuperGameEngine;
using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetFileProvider::ToolsAssetFileProvider(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<TextureManager>& texture)
{
    m_gamePackage = package;
    m_textureManager = texture;

    auto folder = std::make_shared<ToolsAssetFolder>(package, texture, "");
    m_rootFolder = folder;
    folder->PopulateChildren(m_rootFolder);
}

std::vector<std::shared_ptr<AssetFolder>> ToolsAssetFileProvider::GetFoldersInRootDirectory() const
{
    return m_rootFolder->GetContainingFolders();
}

std::vector<std::shared_ptr<AssetFile>> ToolsAssetFileProvider::GetFilesInRootDirectory() const
{
    return m_rootFolder->GetContainingFiles();
}

std::shared_ptr<AssetFolder> ToolsAssetFileProvider::GetRootFolder() const
{
    return m_rootFolder;
}
