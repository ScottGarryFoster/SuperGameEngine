#pragma once
#include <string>
#include <vector>

#include "AssetLayoutEditorFactory.h"

namespace FatedQuestLibraries
{
    enum class UniversalStorableType : uint8_t;
}

namespace SuperGameTools
{
    enum class AssetTemplateLayoutMapType : uint8_t;

    /// <summary>
    /// Creates AssetLayoutEditor objects.
    /// </summary>
    class ToolsAssetLayoutEditorFactory : public AssetLayoutEditorFactory
    {
    public:
        /// <summary>
        /// Creates AssetLayout from a document node.
        /// </summary>
        /// <param name="node">Node loaded from a document. </param>
        /// <returns>Created Asset layout or empty if invalid. </returns>
        virtual std::shared_ptr<AssetLayoutEditor> Create(
            const std::shared_ptr<const FatedQuestLibraries::StoredDocumentNode>& node) const override;

    private:
        /// <summary>
        /// Extracts parameter type.
        /// </summary>
        /// <param name="node">Node to extract from. </param>
        /// <returns>Type of the parameter.</returns>
        FatedQuestLibraries::UniversalStorableType ExtractType(
            const std::shared_ptr<const FatedQuestLibraries::StoredDocumentNode>& node) const;

        /// <summary>
        /// Extracts the Map type from the node.
        /// </summary>
        /// <param name="node">Node to extract from. </param>
        /// <returns>Map type or Unknown if none. </returns>
        AssetTemplateLayoutMapType ExtractMapType(
            const std::shared_ptr<const FatedQuestLibraries::StoredDocumentNode>& node) const;

        /// <summary>
        /// Extract the map itself which is the parameter string to set.
        /// </summary>
        /// <param name="node">Node to extract from. </param>
        /// <returns>Map to set to or string empty. </returns>
        std::string ExtractMap(
            const std::shared_ptr<const FatedQuestLibraries::StoredDocumentNode>& node) const;

        /// <summary>
        /// Extracts the enum filter tag.
        /// </summary>
        /// <param name="node">Node to extract from.</param>
        /// <returns>
        /// The list of filters if any found.
        /// If not enum is found or the tag is not found this is empty.
        /// </returns>
        std::vector<std::string> ExtractEnumFilter(
            const std::shared_ptr<const FatedQuestLibraries::StoredDocumentNode>& node) const;


    };
}
