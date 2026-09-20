#include "ToolsTilesetAssetBrowserAsset.h"
#include "../../../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../../../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "Engine/Content/TextureManager.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsTilesetAssetBrowserAsset::ToolsTilesetAssetBrowserAsset(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<SuperGameEngine::TextureManager>& texture, 
    const std::string& packagePath,
    const std::weak_ptr<AssetFolder>& parent) :
    ToolsAssetFile(package, texture, packagePath, parent)
{
    Setup(package, texture, packagePath, parent);
}

ToolsTilesetAssetBrowserAsset::ToolsTilesetAssetBrowserAsset(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<SuperGameEngine::TextureManager>& texture, 
    const std::string& packagePath,
    const std::weak_ptr<AssetFolder>& parent, 
    const std::shared_ptr<const SingleAssetLayoutMetaData>& assetMetaData)
    : ToolsAssetFile(package, texture, packagePath, parent, assetMetaData)
{
    Setup(package, texture, packagePath, parent);
}
void ToolsTilesetAssetBrowserAsset::Setup(const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
    const std::weak_ptr<SuperGameEngine::TextureManager>& texture, 
    const std::string& packagePath,
    const std::weak_ptr<AssetFolder>& parent)
{
    if (std::shared_ptr<SuperGameEngine::TextureManager> textureManager = texture.lock())
    {
        std::string originalFilePath = Directory::CombinePath("Engine", "TestImages", "A_pressed.png");
        m_largeTilePreview = textureManager->GetTexture(originalFilePath);
        if (!m_largeTilePreview)
        {
            Log::Error("Could not load large tile preview from Texture Manager. Path: " + packagePath, "ToolsTilesetAssetBrowserAsset::ToolsImageAsset");
        }
    }
}
