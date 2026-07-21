#pragma once
#include "../SuperGameAsset.h"
#include "TextureAsset.h"
#include "Structural/Spatial/Area/RectangleInt.h"
#include <memory>

namespace SuperGameEngine
{
    enum class SplitUVMethod : uint8_t;
    class TextureManager;
    class SuperTexture;

    /// <summary>
    /// Describes a texture asset loaded from file.
    /// This has more information than simply the texture itself, it also contains the intended use
    /// of the file such as how to split up the file and how best to render the image to screen.
    /// </summary>
    class SuperTextureAsset : public virtual TextureAsset, public SuperGameAsset
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="universalObject">
        /// Universal object as a stored document.
        /// </param>
        /// <param name="path">
        /// Path to the file which loaded this actual asset.
        /// </param>
        /// <param name="textureManager">
        /// A method to acquire textures, for SuperTextureAsset we need SuperTextures
        /// as this type wraps that level of texture.
        /// </param>
        SuperTextureAsset(
            const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject,
            const std::string& path,
            const std::weak_ptr<TextureManager>& textureManager);

        /// <summary>
        /// Draws to screen at the default position and size.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Draws to screen at the default position and size.
        /// </summary>
        /// <param name="tintColour">Colour to tint the texture. Alpha and also be applied with this. </param>
        virtual void Draw(const FatedQuestLibraries::FColour& tintColour) const override;

        /// <summary>
        /// Draws the tile as defined by the asset meta file.
        /// </summary>
        /// <param name="tile">
        /// The texture tile to render.
        /// </param>
        virtual void Draw(int tile) const override;

        /// <summary>
        /// Draws the tile as defined by the asset meta file.
        /// </summary>
        /// <param name="tile"> The texture tile to render. </param>
        /// <param name="screenLocation"> The location of the texture on screen. </param>
        virtual void Draw(int tile, const FatedQuestLibraries::FVector2F& screenLocation) const override;

        /// <summary>
        /// Draws the tile as defined by the asset meta file.
        /// </summary>
        /// <param name="tile"> The texture tile to render. </param>
        /// <param name="screenLocation"> The location of the texture on screen. </param>
        /// <param name="tintColour">Colour to tint the texture. Alpha and also be applied with this. </param>
        virtual void Draw(
            int tile,
            const FatedQuestLibraries::FVector2F& screenLocation,
            const FatedQuestLibraries::FColour& tintColour) const override;

        /// <summary>
        /// Gets the size of a single tile or the entire image if tiles are not used.
        /// </summary>
        /// <returns>Gets the size of a single tile or the entire image if tiles are not used. </returns>
        virtual FatedQuestLibraries::FVector2I SizeOfSingleTile() const override;

    private:

        /// <summary>
        /// The texture this asset describes.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_superTexture;

        /// <summary>
        /// The texture uv bounds (the size of the texture as an area to compare to).
        /// </summary>
        RectangleInt m_uvBounds;

        /// <summary>
        /// The path for the asset we represent.
        /// </summary>
        std::string m_path;

        /// <summary>
        /// The method the UVs are split by and defined in the file.
        /// </summary>
        SplitUVMethod m_splitMethod;

        /// <summary>
        /// When using predefined UVs these are all the UVs which can be used
        /// upon a texture.
        /// </summary>
        std::vector<std::pair<bool, RectangleInt>> m_predefinedUVs;

        /// <summary>
        /// Gets the size of a single tile or the entire image if tiles are not used.
        /// </summary>
        FatedQuestLibraries::FVector2I m_singleTileSize;

        /// <summary>
        /// Sets up the Predefined UVs upon a texture.
        /// These are all the locations upon a texture you may render.
        /// </summary>
        void SetupPredefinedUVs();

        void DrawPredefined(int tile) const;

        void DrawPredefined(int tile, const FatedQuestLibraries::FVector2F& screenLocation) const;

        void DrawPredefined(int tile, const FatedQuestLibraries::FVector2F& screenLocation, const FatedQuestLibraries::FColour& tintColour) const;

        /// <summary>
        /// Gather and figure out the correct screen rectangle and texture rectangle
        /// when given the tile and location.
        /// This can fail.
        /// </summary>
        /// <param name="tile">Tile to render. </param>
        /// <param name="screenLocation">Where to place the texture on the screen.</param>
        /// <returns>Key is Texture Rectangle, Value is Screen Rectangle, can be in Error check with, HasAnError(). </returns>
        FatedQuestLibraries::KeyPairValueReturn<RectangleInt, RectangleInt>
            GatherScreenSizeAndLocation(int tile, const FatedQuestLibraries::FVector2F& screenLocation) const;

        /// <summary>
        /// Draws a texture to screen exactly as passed in.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        virtual void DrawImplementation(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const;

        /// <summary>
        /// Draws a texture to screen exactly as passed in.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        /// <param name="tintColour">Colour to tint the texture. Alpha and also be applied with this. </param>
        virtual void DrawImplementation(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle, const FatedQuestLibraries::FColour& tintColour) const;
    };
}

