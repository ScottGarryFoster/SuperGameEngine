#include "SuperTextureAssetFactory.h"

#include "Structural/Assets/Texture/SuperTextureAsset.h"

using namespace SuperGameEngine;

std::shared_ptr<SuperTextureAsset> SuperTextureAssetFactory::Create(
    const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject, 
    const std::string& path,
    const std::weak_ptr<TextureManager>& textureManager) const
{
    return std::make_shared<SuperTextureAsset>(universalObject, path, textureManager);
}
