#include "SuperTilesetAsset.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperTilesetAsset::SuperTilesetAsset(
    const std::shared_ptr<StoredDocument>& universalObject, const std::string& path,
    const std::weak_ptr<TextureManager>& textureManager) : SuperGameAsset(universalObject, path)
{
    
}

std::vector<std::shared_ptr<TextureAsset>> SuperTilesetAsset::GetStandardTextures() const
{
    return m_textureAssets;
}
