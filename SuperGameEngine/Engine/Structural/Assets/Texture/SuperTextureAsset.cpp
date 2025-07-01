#include "SuperTextureAsset.h"
#include <Engine/Content/TextureManager.h>
#include <Engine/Graphics/Texture/SuperTexture.h>

#include "SplitUVMethod.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperTextureAsset::SuperTextureAsset(
    const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject, 
    const std::string& path,
    const std::weak_ptr<TextureManager>& textureManager)
    : SuperGameAsset(universalObject, path)
{

    m_splitMethod = SplitUVMethod::Unknown;

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

    m_uvBounds = RectangleInt(0, 0, m_superTexture->Size().GetX(), m_superTexture->Size().GetY());

    if (IsStringLoaded("TextureUVMethod"))
    {
        m_splitMethod = ESplitUVMethod::FromString(GetString("TextureUVMethod"));
    }

    switch (m_splitMethod)
    {
        case SplitUVMethod::Predefined: SetupPredefinedUVs(); break;
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
    if (m_superTexture)
    {
        switch (m_splitMethod)
        {
        case SplitUVMethod::Predefined:
            DrawPredefined(tile);
            break;
        default:
            m_superTexture->Draw();
        }
    }
}

void SuperTextureAsset::SetupPredefinedUVs()
{
    int vectors = 0;
    while (true)
    {
        std::string uvKey = "TextureUV" + std::to_string(vectors);
        if (IsVector4ILoaded(uvKey))
        {
            ++vectors;
        }
        else
        {
            break;
        }
    }

    m_predefinedUVs.clear();
    m_predefinedUVs.resize(vectors);
    for (int i = 0 ; i < vectors; ++i)
    {
        std::string uvKey = "TextureUV" + std::to_string(i);
        std::shared_ptr<FVector4I> vectorUV = GetVector4I(uvKey);

        auto textureUV = RectangleInt(vectorUV);
        bool newUVIsValid = m_uvBounds.Contains(textureUV);
        if (!newUVIsValid)
        {
            Log::Error("Loaded a texture UV outside the bounds of a texture. "
                       "Texture: " + m_uvBounds.ToString() + "UV: " + textureUV.ToString(),
                "SuperTextureAsset::SetupPredefinedUVs");
        }

        m_predefinedUVs[i] = { newUVIsValid, vectorUV };
    }
}

void SuperTextureAsset::DrawPredefined(int tile) const
{
    if (tile < 0)
    {
        return;
    }

    // Cast to Size_T to remove warning here.
    // We are never going to use so many segments as to reach the int limit.
    if (static_cast<size_t>(tile) >= m_predefinedUVs.size())
    {
        return;
    }

    // If the bool is false, the rectangle is invalid
    if (!m_predefinedUVs[tile].first)
    {
        return;
    }

    m_superTexture->Draw(m_predefinedUVs[tile].second, m_predefinedUVs[tile].second);
}
