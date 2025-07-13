#pragma once
#include <memory>

#include "AssetFolderRender.h"
#include "../../FatedQuestLibraries.h"

namespace FatedQuestLibraries
{
    class FEventArguments;
}

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
    class AssetFile;
}

namespace SuperGameTools
{
    /// <summary>
    /// Renders the folder as tiles.
    /// </summary>
    class AssetTileRender : public AssetFolderRender, public FatedQuestLibraries::FEventObserver
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

        /// <summary>
        /// Called when we need to update.
        /// Expect: PackageFilesHaveUpdatedEventArguments for new asset folder.
        /// </summary>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

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

        /// <summary>
        /// Texture to move back up folders.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_upFolderTexture;

        /// <summary>
        /// Draws a folder tile.
        /// </summary>
        /// <param name="folder">Folder to draw. </param>
        /// <param name="size">Size of the tile. </param>
        /// <param name="padding">Padding between tiles. </param>
        /// <returns>Folder to move to if an action is taken. </returns>
        std::shared_ptr<AssetFolder> DrawFolder(
            const std::shared_ptr<AssetFolder>& folder, 
            int size, 
            int padding) const;

        /// <summary>
        /// Draws a return folder tile.
        /// </summary>
        /// <param name="previousFolder">Folder above this. </param>
        /// <param name="size">Size of the tile. </param>
        /// <param name="padding">Padding between tiles. </param>
        /// <returns>True means do return. </returns>
        bool DrawReturnFolder(
            const std::shared_ptr<AssetFolder>& previousFolder,
            int size,
            int padding) const;

        /// <summary>
        /// Draws a file tile.
        /// </summary>
        /// <param name="file">File to draw. </param>
        /// <param name="size">Size of the tile. </param>
        /// <param name="padding">Padding between tiles. </param>
        /// <returns>The file clicked if any. </returns>
        std::shared_ptr<AssetFile> DrawFile(
            const std::shared_ptr<AssetFile>& file,
            int size,
            int padding) const;
    };
}
