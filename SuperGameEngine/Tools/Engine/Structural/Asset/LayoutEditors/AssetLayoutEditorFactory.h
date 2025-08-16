#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

namespace SuperGameTools
{
    class AssetLayoutEditor;

    /// <summary>
    /// Creates AssetLayoutEditor objects.
    /// </summary>
    class AssetLayoutEditorFactory
    {
    public:
        /// <summary>
        /// Creates AssetLayout from a document node.
        /// </summary>
        /// <param name="node">Node loaded from a document. </param>
        /// <returns>Created Asset layout or empty if invalid. </returns>
        virtual std::shared_ptr<AssetLayoutEditor> Create(
            const std::shared_ptr<const FatedQuestLibraries::StoredDocumentNode>& node) const = 0;
    };
}
