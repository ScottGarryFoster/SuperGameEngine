#include "ToolsImageAsset.h"
#include "FatedQuestLibraries.h"
#include "../../../Engine/Engine/Content/TextureManager.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

ToolsImageAsset::ToolsImageAsset(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<TextureManager>& texture, 
    const std::string& packagePath,
    const std::weak_ptr<AssetFolder>& parent) :
    ToolsAssetFile(package, texture, packagePath, parent)
{
    Setup(package, texture, packagePath, parent);
}

ToolsImageAsset::ToolsImageAsset(
    const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
    const std::weak_ptr<SuperGameEngine::TextureManager>& texture, 
    const std::string& packagePath,
    const std::weak_ptr<AssetFolder>& parent, 
    const std::shared_ptr<const AssetMetaData>& assetMetaData)
    : ToolsAssetFile(package, texture, packagePath, parent, assetMetaData)
{
    Setup(package, texture, packagePath, parent);
}

void ToolsImageAsset::Setup(
    const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
    const std::weak_ptr<SuperGameEngine::TextureManager>& texture, 
    const std::string& packagePath,
    const std::weak_ptr<AssetFolder>& parent)
{
    if (std::shared_ptr<GamePackage> gamePackage = package.lock())
    {
        std::string originalFilePath = File::RemoveLastExtension(packagePath);

        // Setup the image.
        if (std::shared_ptr<TextureManager> textureManager = texture.lock())
        {
            std::string fileType = File::GetExtension(originalFilePath);
            if (StringHelpers::ToLower(fileType) == ".png")
            {
                m_largeTilePreview = textureManager->GetTexture(originalFilePath);
                if (!m_largeTilePreview)
                {
                    Log::Error("Could not load large tile preview from Texture Manager. Path: " + packagePath, "ToolsImageAsset::ToolsImageAsset");
                }
            }
        }
        else
        {
            Log::Error("Texture Manager is not given. Path: " + packagePath, "ToolsImageAsset::ToolsImageAsset");
        }
    }
    else
    {
        Log::Error("Package manager is not given, asset not loaded. Path: " + packagePath, "ToolsImageAsset::ToolsImageAsset");
    }
}
