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
    m_parent = {};

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

std::weak_ptr<AssetFolder> ToolsAssetFolder::GetParent() const
{
    return m_parent;
}

void ToolsAssetFolder::PopulateChildren(const std::weak_ptr<AssetFolder>& parent)
{
    // Keep in mind, at the root this will be an empty pointer to nothing.
    m_parent = parent;

    // Populate might occur after files and folders have loaded.
    m_files.clear();
    m_folders.clear();

    if (std::shared_ptr<GamePackage> gamePackage = m_gamePackage.lock())
    {
        std::vector<std::string> fileList = gamePackage->Directory()->GetFiles(m_packagePath);
        for (const std::string& fileName : fileList)
        {
            std::string extension = File::GetExtension(fileName);
            if (StringHelpers::ToLower(extension) != ".ast")
            {
                continue;
            }

            std::string assetFilePackagePath = Directory::CombinePath(m_packagePath, fileName);

            std::shared_ptr<ToolsAssetFile> file = {};
            try
            {
                file = std::make_shared<ToolsAssetFile>(m_gamePackage, m_textureManager, assetFilePackagePath, shared_from_this());
                m_files.emplace_back(file);
            }
            catch (const std::exception& e)
            {
                Log::Error("Asset File could not be created: " + assetFilePackagePath + ". " +
                    e.what()
                    ,"ToolsAssetFolder::PopulateChildren(const std::weak_ptr<AssetFolder>&)");
            }
        }

        std::vector<std::string> directoryList = gamePackage->Directory()->ListDirectories(m_packagePath);
        for (const std::string& directoryPath : directoryList)
        {
            auto folder = std::make_shared<ToolsAssetFolder>(m_gamePackage, m_textureManager, directoryPath);
            folder->PopulateChildren(shared_from_this());
            m_folders.emplace_back(folder);
        }
    }
}
