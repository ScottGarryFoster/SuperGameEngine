#pragma once
#include <memory>
#include <unordered_set>

#include "AssetTemplate.h"
#include "../../UniversalObjectData/Template/UniversalObjectDataTemplateCreationMethod.h"
#include "../../UniversalObjectData/Template/UniversalObjectDataTemplateMatchingStyle.h"
#include "Engine/Structural/UniversalObjectData/Template/ToolsUniversalTemplate.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class StoredDocument;
}

namespace SuperGameTools
{
    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// </summary>
    class ToolsAssetTemplate : public ToolsUniversalTemplate, public virtual AssetTemplate
    {
    public:

        ToolsAssetTemplate(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode);

        /// <summary>
        /// Gets the file type to create when creating a <see cref="AssetFile"/>.
        /// <see cref="AssetFileType::Unknown"/> means there is none set and the default should be used.
        /// </summary>
        /// <returns>The file type to be created. </returns>
        virtual AssetFileType GetAssetFileType() const override;

    private:

        /// <summary>
        /// The file type to create when creating a <see cref="AssetFile"/>.
        /// <see cref="AssetFileType::Unknown"/> means there is none set and the default should be used.
        /// </summary>
        AssetFileType m_assetFileType;

#pragma region Root Parsing

        /// <summary>
        /// Parses the root node attributes.
        /// </summary>
        /// <param name="rootNode">Root template node.</param>
        void ParseRootAttributes(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& rootNode);

#pragma endregion

    };
}
