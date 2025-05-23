#pragma once
#include "../SuperGameAsset.h"
#include "TextureAsset.h"
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
        /// Draws the tile as defined by the asset meta file.
        /// </summary>
        /// <param name="tile">
        /// The texture tile to render.
        /// </param>
        virtual void Draw(int tile) const override;

    private:

        /// <summary>
        /// The texture this asset describes.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_superTexture;

        /// <summary>
        /// The path for the asset we represent.
        /// </summary>
        std::string m_path;

        /// <summary>
        /// The method the UVs are split by and defined in the file.
        /// </summary>
        SplitUVMethod m_splitMethod;
    };
}

