#include "SuperTextureAsset.h"
#include <Engine/Content/TextureManager.h>
#include <Engine/Graphics/Texture/SuperTexture.h>

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperTextureAsset::SuperTextureAsset(
    const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject, 
    const std::string& path,
    const std::weak_ptr<TextureManager>& textureManager)
    : SuperGameAsset(universalObject, path)
{

    m_path = File::Sanitize(path);
    if (m_path.empty())
    {
        Log::Exception("Path is null or whitespace, unable to create asset.",
            "SuperGameEngine::SuperTextureAsset::SuperTextureAsset",
            "InvalidArgumentException");
        return;
    }

    if (std::shared_ptr<TextureManager> tm = textureManager.lock())
    {
        m_superTexture = tm->GetTexture(m_path);
        if (!m_superTexture)
        {
            Log::Exception("Could not create Texture Asset based on the following path: " + m_path,
                "SuperGameEngine::SuperTextureAsset::SuperTextureAsset",
                "InvalidArgumentException");
            return;
        }
    }
    else
    {
        Log::Exception("No texture manager passed into SuperTextureAsset, unable to acquire texture.",
            "SuperGameEngine::SuperTextureAsset::SuperTextureAsset",
            "InvalidArgumentException");
        return;
    }
}

void SuperTextureAsset::Draw() const
{
    if (m_superTexture)
    {
        m_superTexture->Draw();
    }
}

void SuperTextureAsset::Draw(int tile) const
{

}
