#pragma once
#include <memory>
#include <vector>

#include "AssetLayout.h"

namespace FatedQuestLibraries
{
    class Guid;
    class StoredDocumentNode;
}

namespace SuperGameTools
{
    class AssetLayoutEditorFactory;

    /// <summary>
    /// Describes how to edit the given asset and how the data is laid out.
    /// </summary>
    class ToolsAssetLayout : public AssetLayout
    {
    public:

        ToolsAssetLayout(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode,
            const std::shared_ptr<AssetLayoutEditorFactory>& layoutFactory);

        /// <summary>
        /// Update loop call for the given asset to prepare anything for the layout.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        virtual void Update(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

        /// <summary>
        /// Draws and may alter the data within the asset.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void Draw(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

    private:

        /// <summary>
        /// The size of the left column in pixels.
        /// </summary>
        const float m_sizeOfLeftColumn = 200;

        /// <summary>
        /// The editor providing the structure to edit the data.
        /// </summary>
        std::vector<std::shared_ptr<const AssetLayoutEditor>> m_assetLayoutEditor;
    };
}
