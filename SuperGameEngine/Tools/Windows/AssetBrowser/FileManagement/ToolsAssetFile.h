#pragma once
#include "AssetFile.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameEngine
{
    class TextureManager;
    class GameAsset;
    class SuperTexture;
}

namespace SuperGameTools
{
    /// <summary>
    /// Implementation of <see cref="AssetFile"/>
    /// </summary>
    class ToolsAssetFile : public AssetFile
    {
    public:

        ToolsAssetFile(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath, 
            const std::weak_ptr<AssetFolder>& parent);

        /// <summary>
        /// Gets the parent folder.
        /// </summary>
        /// <returns>The parent of the given file. </returns>
        virtual std::weak_ptr<AssetFolder> GetParent() const override;

        /// <summary>
        /// Get the name to display in a browser.
        /// </summary>
        /// <returns>The display name. </returns>
        virtual std::string GetDisplayName() const override;

        /// <summary>
        /// Get the path to this file in relation to the package.
        /// </summary>
        /// <returns>The path relative to the products folder. </returns>
        virtual std::string GetPackagePath() const override;

        /// <summary>
        /// Draws an image representing the file with the given size.
        /// </summary>
        /// <param name="screenRectangle">Location and size on the screen to draw. </param>
        virtual void DrawLargeTile(const SuperGameEngine::RectangleInt& screenRectangle) const override;

    private:

        /// <summary>
        /// Loaded asset data.
        /// </summary>
        std::shared_ptr<SuperGameEngine::GameAsset> m_gameAsset;

        /// <summary>
        /// Texture for the large tile.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_largeTilePreview;

        /// <summary>
        /// Out parent folder.
        /// </summary>
        std::weak_ptr<AssetFolder> m_parent;
    };
}
