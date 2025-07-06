#pragma once
#include <memory>

#include "AssetFolderRender.h"

namespace SuperGameEngine
{
    class TextureManager;
}

namespace SuperGameEngine
{
    class SuperTexture;
}

namespace SuperGameTools
{
    class AssetFolder;
}

namespace SuperGameTools
{
    /// <summary>
    /// Renders the folder as tiles.
    /// </summary>
    class AssetTileRender : public AssetFolderRender
    {
    public:

        AssetTileRender(
            const std::shared_ptr<AssetFolder>& rootFolder, 
            const std::shared_ptr<SuperGameEngine::TextureManager>& texture);

        /// <summary>
        /// An update loop ran before the draw.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Render the asset tiles.
        /// </summary>
        virtual void Draw() override;

    private:
        /// <summary>
        /// The root folder.
        /// </summary>
        std::shared_ptr<AssetFolder> m_rootFolder;

        /// <summary>
        /// Current folder navigated to.
        /// </summary>
        std::shared_ptr<AssetFolder> m_currentFolder;

        /// <summary>
        /// Texture to use for folders.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_folderTexture;
    };
}
