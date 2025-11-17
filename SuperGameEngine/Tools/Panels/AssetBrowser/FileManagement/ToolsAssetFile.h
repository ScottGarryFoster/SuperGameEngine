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
    class ToolsAssetFile : public virtual AssetFile
    {
    public:

        ToolsAssetFile(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent);

        ToolsAssetFile(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent,
            const std::shared_ptr<const AssetMetaData>& assetMetaData);

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

        /// <summary>
        /// Selects this file or tile.
        /// </summary>
        virtual void SelectFile() override;

        /// <summary>
        /// Unselects this file or tile.
        /// </summary>
        virtual void UnselectFile() override;

        /// <summary>
        /// True means the file is selected in the browser.
        /// </summary>
        /// <returns>True means the file is selected in the browser. </returns>
        virtual bool IsSelected() const override;

        /// <summary>
        /// Get the metadata for this file type. This describes. how to edit the file.
        /// </summary>
        /// <returns>The metadata for this file type. This describes. how to edit the file. </returns>
        virtual const std::shared_ptr<const AssetMetaData> GetMetaData() const override;

        /// <summary>
        /// Describes the group for the selectable which helps to decide the
        /// buckets that the selectable will be added to.
        /// </summary>
        /// <returns>The group or groups for this selectable. </returns>
        virtual std::unordered_set<SelectionGroup> GetSelectionGroup() const override;

        /// <summary>
        /// The Guid for this Selectable.
        /// It should be unique among selectables.
        /// </summary>
        /// <returns>A unique Guid. </returns>
        virtual std::shared_ptr<Guid> GetGuid() const override;

        /// <summary>
        /// Gets the raw interaction state.
        /// This describes how the tile is being interacted with and should describe the whole tile
        /// not just the image but is stored here.
        /// </summary>
        /// <returns>Describes interactions to the Asset Tiles rendered via the Asset Browser. </returns>
        virtual AssetTileInteractionRawState GetAssetTileInteractionRawState() const override;

        /// <summary>
        /// Sets the raw interaction state.
        /// This describes how the tile is being interacted with and should describe the whole tile
        /// not just the image but is stored here.
        /// </summary>
        /// <param name="newValue">New Raw State. </param>
        virtual void SetAssetTileInteractionRawState(AssetTileInteractionRawState newValue) override;

    protected:

        /// <summary>
        /// Texture for the large tile.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_largeTilePreview;

    private:

        /// <summary>
        /// The default asset tile if one does not exist.
        /// </summary>
        const char* m_defaultAssetTexture = "Tools\\Icons\\AssetDefault\\AssetDefault-500.png";

        /// <summary>
        /// Loaded asset data.
        /// </summary>
        std::shared_ptr<SuperGameEngine::GameAsset> m_gameAsset;

        /// <summary>
        /// Describes what asset metadata files are exactly, what files they relate to, how to edit them and so on.
        /// </summary>
        std::shared_ptr<const AssetMetaData> m_assetMetaData;

        /// <summary>
        /// Out parent folder.
        /// </summary>
        std::weak_ptr<AssetFolder> m_parent;

        /// <summary>
        /// A unique identifier.
        /// A GUID should be unique.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// The groups for this selectable.
        /// </summary>
        std::unordered_set<SelectionGroup> m_selectionGroups;

        /// <summary>
        /// The file is selected currently and is in the inspector.
        /// </summary>
        bool m_selected;

        /// <summary>
        /// Describes interactions to the Asset Tiles rendered via the Asset Browser.
        /// </summary>
        AssetTileInteractionRawState m_assetTileInteractionRawState;
    };
}
