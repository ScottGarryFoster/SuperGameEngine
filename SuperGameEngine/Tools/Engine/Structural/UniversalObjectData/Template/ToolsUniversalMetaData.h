#pragma once
#include "SingleLayoutMetaData.h"

namespace FatedQuestLibraries
{
    class StoredDocument;
}

namespace SuperGameTools
{
    class LayoutEditorFactory;

    /// <summary>
    /// Describes what asset metadata files are exactly, what files they relate to, how to edit them and so on.
    /// </summary>
    class ToolsUniversalMetaData : public SingleLayoutMetaData
    {
    public:
        ToolsUniversalMetaData(
            const std::shared_ptr<FatedQuestLibraries::StoredDocument>& document,
            const std::shared_ptr<LayoutEditorFactory>& layoutFactory);

        /// <summary>
        /// Contains a template and the ability to detect whether using the template is correct.
        /// Templates also contain the ability to create fresh versions of the Asset file.
        /// </summary>
        /// <returns>The template for this asset metadata. </returns>
        virtual std::shared_ptr<UniversalObjectDataTemplate> GetTemplate() const override;

        /// <summary>
        /// Get the layout for the asset, this is how to display edits and how the data
        /// itself should be treated.
        /// </summary>
        /// <returns>Describes how to edit the given asset and how the data is laid out. </returns>
        virtual std::shared_ptr<SingleLayout> GetLayout() const override;

    private:
        /// <summary>
        /// Template for the data.
        /// </summary>
        std::shared_ptr<UniversalObjectDataTemplate> m_template;

        /// <summary>
        /// Layout for the data.
        /// </summary>
        std::shared_ptr<SingleLayout> m_layout;
    };
}

