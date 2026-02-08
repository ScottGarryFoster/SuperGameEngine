#include "ToolsTextureAssetFactory.h"

#include "Structural/Assets/Texture/SuperTextureAsset.h"

std::shared_ptr<SuperGameEngine::SuperTextureAsset> SuperGameTools::ToolsTextureAssetFactory::Create(
    const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject, 
    const std::string& path,
    const std::weak_ptr<SuperGameEngine::TextureManager>& textureManager) const
{
    return std::make_shared<SuperGameEngine::SuperTextureAsset>(universalObject, path, textureManager);
}
