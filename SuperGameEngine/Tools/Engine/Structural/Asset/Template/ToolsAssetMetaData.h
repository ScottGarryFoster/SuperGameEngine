#pragma once
#include "AssetMetaData.h"

namespace FatedQuestLibraries
{
    class StoredDocument;
}

namespace SuperGameTools
{
    /// <summary>
    /// Describes what asset metadata files are exactly, what files they relate to, how to edit them and so on.
    /// </summary>
    class ToolsAssetMetaData : public AssetMetaData
    {
    public:
        ToolsAssetMetaData(const std::shared_ptr<FatedQuestLibraries::StoredDocument>& document);

        /// <summary>
        /// Contains a template and the ability to detect whether using the template is correct.
        /// Templates also contain the ability to create fresh versions of the Asset file.
        /// </summary>
        /// <returns>The template for this asset metadata. </returns>
        virtual std::shared_ptr<AssetTemplate> GetTemplate() const override;

        /// <summary>
        /// Get the layout for the asset, this is how to display edits and how the data
        /// itself should be treated.
        /// </summary>
        /// <returns>Describes how to edit the given asset and how the data is laid out. </returns>
        virtual std::shared_ptr<AssetLayout> GetLayout() const override;

    private:
        /// <summary>
        /// Template for the asset.
        /// </summary>
        std::shared_ptr<AssetTemplate> m_template;

        /// <summary>
        /// Layout for the asset.
        /// </summary>
        std::shared_ptr<AssetLayout> m_layout;
    };
}

