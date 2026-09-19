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
    m_uniformByPixelTilesPerRow = 0;
    m_uniformByPixelMaxTiles = 0;
    m_singleTileSize = { .X = 0,.Y = 0 };

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
        case SplitUVMethod::UniformByPixel: SetupUniformByPixelUVs(); break;
    }

    // If the setup is broken just default to the size of the texture.
    if (m_splitMethod == SplitUVMethod::Unknown)
    {
        m_singleTileSize = { .X = m_superTexture->Size().GetX(), .Y = m_superTexture->Size().GetY() };
    }
}

void SuperTextureAsset::Draw() const
{
    if (m_superTexture)
    {
        m_superTexture->Draw();
    }
}

void SuperTextureAsset::Draw(const FatedQuestLibraries::FColour& tintColour) const
{
    if (m_superTexture)
    {
        m_superTexture->Draw(tintColour);
    }
}

void SuperTextureAsset::Draw(int tile) const
{
    if (m_superTexture)
    {
        switch (m_splitMethod)
        {
        case SplitUVMethod::Predefined: DrawPredefined(tile); break;
        case SplitUVMethod::UniformByPixel: DrawUniformByPixel(tile); break;
        default:
            m_superTexture->Draw();
        }
    }
}

void SuperTextureAsset::Draw(int tile, const FVector2F& screenLocation) const
{
    if (m_superTexture)
    {
        switch (m_splitMethod)
        {
        case SplitUVMethod::Predefined:DrawPredefined(tile, screenLocation); break;
        case SplitUVMethod::UniformByPixel: DrawUniformByPixel(tile, screenLocation); break;
        default:
            m_superTexture->Draw(FPoint(screenLocation.GetX(), screenLocation.GetY()));
        }
    }
}

void SuperTextureAsset::Draw(int tile, const FVector2F& screenLocation, const FColour& tintColour) const
{
    if (m_superTexture)
    {
        switch (m_splitMethod)
        {
        case SplitUVMethod::Predefined: DrawPredefined(tile, screenLocation, tintColour); break;
        case SplitUVMethod::UniformByPixel: DrawUniformByPixel(tile, screenLocation, tintColour); break;
        default:
            m_superTexture->Draw(FPoint(static_cast<int>(screenLocation.GetX()), static_cast<int>(screenLocation.GetY())), tintColour);
        }
    }
}

FVector2I SuperTextureAsset::SizeOfSingleTile() const
{
    return {m_singleTileSize.X, m_singleTileSize.Y};
}

void SuperTextureAsset::SetupPredefinedUVs()
{
    int vectors = 0;
    while (true)
    {
        if (IsVector4ILoaded("TextureUV" + std::to_string(vectors)))
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
        std::shared_ptr<FVector4I> vectorUV = GetVector4I("TextureUV" + std::to_string(i));

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

    if (m_predefinedUVs.empty())
    {
        Log::Exception("No UV setup with method setup for UVs. Method: " + ESplitUVMethod::ToString(m_splitMethod),
            "void SuperTextureAsset::SetupPredefinedUVs()",
            "Exception");

        m_splitMethod = SplitUVMethod::Unknown;
        return;
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

    m_superTexture->Draw(m_predefinedUVs[tile].second, RectangleInt());
}

void SuperTextureAsset::DrawPredefined(int tile, const FVector2F& screenLocation) const
{
    KeyPairValueReturn<RectangleInt, RectangleInt> screenSizeAndLocation = GatherScreenSizeAndLocation(tile, screenLocation);
    if (screenSizeAndLocation.HasAnError())
    {
        return;
    }

    DrawImplementation(screenSizeAndLocation.Key, screenSizeAndLocation.Value);
}

void SuperTextureAsset::DrawPredefined(
    int tile, 
    const FatedQuestLibraries::FVector2F& screenLocation,
    const FatedQuestLibraries::FColour& tintColour) const
{
    KeyPairValueReturn<RectangleInt, RectangleInt> screenSizeAndLocation = GatherScreenSizeAndLocation(tile, screenLocation);
    if (screenSizeAndLocation.HasAnError())
    {
        return;
    }

    DrawImplementation(screenSizeAndLocation.Key, screenSizeAndLocation.Value, tintColour);
}

void SuperTextureAsset::SetupUniformByPixelUVs()
{
    if (IsVector2ILoaded("UniformTextureUV"))
    {
        m_singleTileSize = {
            .X = GetVector2I("UniformTextureUV")->GetX(),
            .Y = GetVector2I("UniformTextureUV")->GetY()
        };
    }

    if (m_singleTileSize.X <= 0 || m_singleTileSize.Y <= 0)
    {
        Log::Error("UniformByPixel is not setup correctly for " + m_path,
            "SuperTextureAsset::SetupUniformByPixelUVs()");
        m_splitMethod = SplitUVMethod::Unknown;
        return;
    }

    int textureWidth = m_superTexture->Size().GetX();
    int textureHeight = m_superTexture->Size().GetY();

    if (m_singleTileSize.X > textureWidth || m_singleTileSize.Y > textureHeight)
    {
        Log::Error("UniformByPixel is not setup correctly, the width or height "
                   "is bigger than the texture for " + m_path,
            "SuperTextureAsset::SetupUniformByPixelUVs()");
        m_splitMethod = SplitUVMethod::Unknown;
        return;
    }

    m_uniformByPixelTilesPerRow = textureWidth / m_singleTileSize.X;
    int tilesInHeight = textureHeight / m_singleTileSize.Y;
    m_uniformByPixelMaxTiles = m_uniformByPixelTilesPerRow * tilesInHeight;
}

void SuperTextureAsset::DrawUniformByPixel(int tile) const
{
    if (tile < 0 || m_uniformByPixelMaxTiles >= tile)
    {
        return;
    }

    int rowBefore = tile / m_uniformByPixelTilesPerRow;
    int xTile = tile - (rowBefore * m_uniformByPixelTilesPerRow);
    int yTile = rowBefore;

    m_superTexture->Draw(RectangleInt(
        xTile * m_singleTileSize.X, 
        yTile * m_singleTileSize.Y, 
        m_singleTileSize.X, 
        m_singleTileSize.Y), RectangleInt());
}

void SuperTextureAsset::DrawUniformByPixel(int tile, const FatedQuestLibraries::FVector2F& screenLocation) const
{
    if (tile < 0 || m_uniformByPixelMaxTiles >= tile)
    {
        return;
    }

    int rowBefore = tile / m_uniformByPixelTilesPerRow;
    int xTile = tile - (rowBefore * m_uniformByPixelTilesPerRow);
    int yTile = rowBefore;

    m_superTexture->Draw(RectangleInt(
        xTile * m_singleTileSize.X,
        yTile * m_singleTileSize.Y,
        m_singleTileSize.X,
        m_singleTileSize.Y), 
        RectangleInt(
            static_cast<int>(screenLocation.GetX()),
            static_cast<int>(screenLocation.GetY()),
            m_singleTileSize.X,
            m_singleTileSize.Y));
}

void SuperTextureAsset::DrawUniformByPixel(int tile, const FatedQuestLibraries::FVector2F& screenLocation,
    const FatedQuestLibraries::FColour& tintColour) const
{
    if (tile < 0 || m_uniformByPixelMaxTiles >= tile)
    {
        return;
    }

    int rowBefore = tile / m_uniformByPixelTilesPerRow;
    int xTile = tile - (rowBefore * m_uniformByPixelTilesPerRow);
    int yTile = rowBefore;

    m_superTexture->Draw(
        RectangleInt(
        xTile * m_singleTileSize.X,
        yTile * m_singleTileSize.Y,
        m_singleTileSize.X,
        m_singleTileSize.Y),
        RectangleInt(
            static_cast<int>(screenLocation.GetX()),
            static_cast<int>(screenLocation.GetY()),
            m_singleTileSize.X,
            m_singleTileSize.Y),
        tintColour);
}

KeyPairValueReturn<RectangleInt, RectangleInt> SuperTextureAsset::GatherScreenSizeAndLocation(
    int tile,
    const FatedQuestLibraries::FVector2F& screenLocation) const
{
    if (tile < 0)
    {
        return {.WasError = true };
    }

    // Cast to Size_T to remove warning here.
    // We are never going to use so many segments as to reach the int limit.
    if (static_cast<size_t>(tile) >= m_predefinedUVs.size())
    {
        return { .WasError = true };
    }

    // If the bool is false, the rectangle is invalid
    if (!m_predefinedUVs[tile].first)
    {
        return { .WasError = true };
    }

    return
    {
        .Key = m_predefinedUVs[tile].second,
        .Value = RectangleInt(
            static_cast<int>(screenLocation.GetX()),
            static_cast<int>(screenLocation.GetY()),
            m_predefinedUVs[tile].second.GetWidth(),
            m_predefinedUVs[tile].second.GetHeight()),
        .WasError = false,
    };
}

void SuperTextureAsset::DrawImplementation(
    const RectangleInt& textureRectangle,
    const RectangleInt& screenRectangle) const
{
    m_superTexture->Draw(textureRectangle, screenRectangle);
}

void SuperTextureAsset::DrawImplementation(
    const RectangleInt& textureRectangle, 
    const RectangleInt& screenRectangle,
    const FColour& tintColour) const
{
    m_superTexture->Draw(textureRectangle, screenRectangle, tintColour);
}
