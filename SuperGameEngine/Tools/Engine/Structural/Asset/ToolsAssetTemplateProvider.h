#pragma once
#include "AssetTemplateProvider.h"
namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameTools
{
    class AssetLayoutEditorFactory;

    /// <summary>
    /// Loads, holds and provides <see cref="AssetTemplate"/> in a single location.
    /// </summary>
    class ToolsAssetTemplateProvider : public AssetTemplateProvider
    {
    public:

        ToolsAssetTemplateProvider(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage);

        /// <summary>
        /// Retrieve all the <see cref="AssetTemplate"/> objects loaded. 
        /// </summary>
        /// <returns>All the <see cref="AssetTemplate"/> objects loaded. </returns>
        virtual std::vector<std::shared_ptr<const AssetMetaData>> GetAssetTemplates() const override;

        /// <summary>
        /// Load all the asset metadata into the provider.
        /// This should only be called once but if it is called again
        /// it will act as a reload and empty the templates it already has.
        /// </summary>
        /// <returns>
        /// True means load was successful.
        /// False means could not load templates.
        /// </returns>
        bool LoadAllAssetMeta();

    private:
        /// <summary>
        /// Where to store the asset templates within the game package.
        /// </summary>
        const char* m_assetTemplateFolder = "Tools\\AssetTemplates";

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// The factory to create layouts.
        /// </summary>
        std::shared_ptr<AssetLayoutEditorFactory> m_assetLayoutEditorFactory;

        /// <summary>
        /// All asset templates.
        /// </summary>
        std::vector<std::shared_ptr<const AssetMetaData>> m_assetTemplates;
    };
}
