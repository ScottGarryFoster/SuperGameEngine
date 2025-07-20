#pragma once
#include <memory>
#include <unordered_set>

#include "AssetTemplate.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

namespace SuperGameTools
{
    enum class AssetTemplateMatchingStyle : uint8_t;

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
        /// <summary>
        /// Describes how a template might figure out if a given file is in fact the template
        /// for which it is defined. For instance does the file path make a match.
        /// </summary>
        AssetTemplateMatchingStyle m_matchingStyle;

        /// <summary>
        /// In some matching criteria the extensions are how a template is matched to the date it relates.
        /// </summary>
        std::unordered_set<std::string> m_matchingExtensions;

        // Matching Criteria Creation

        /// <summary>
        /// Creates the data for MatchingCriteria.
        /// </summary>
        /// <param name="matchingNodeRoot">The MatchingCriteria node. </param>
        void CreateDataForMatchingCriteria(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& matchingNodeRoot);

        /// <summary>
        /// Extract all the extensions which are children of
        /// MatchingCriteria and are values of nodes called Extensions.
        /// </summary>
        /// <param name="matchingNodeRoot">The MatchingCriteria node. </param>
        void CreateDataForMatchingCriteriaExtension(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& matchingNodeRoot);

        // Should Use Template

        bool ShouldUseTemplateExtension(const std::string& filepath) const;
    };
}
