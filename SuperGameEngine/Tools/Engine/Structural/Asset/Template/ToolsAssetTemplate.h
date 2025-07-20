#pragma once
#include <memory>
#include "AssetTemplate.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

namespace SuperGameTools
{
    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// </summary>
    class ToolsAssetTemplate : public AssetTemplate
    {
    public:

        ToolsAssetTemplate(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode);
        virtual ~ToolsAssetTemplate() override;

        /// <summary>
        /// Determines if this template is the one to use.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means this template is correct. </returns>
        virtual bool ShouldUseTemplate(const std::string& filepath) const override;

        /// <summary>
        /// Create an asset file based on the file path.
        /// </summary>
        /// <param name="filepath">Filepath to use as a base. </param>
        /// <returns>An asset file </returns>
        virtual std::string CreateAssetFile(const std::string& filepath) const override;

    private:
    };
}
