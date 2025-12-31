#pragma once
#include <memory>
#include <unordered_set>

#include "UniversalObjectDataTemplate.h"
#include "UniversalTemplate.h"
#include "UniversalObjectDataTemplateCreationMethod.h"
#include "UniversalObjectDataTemplateMatchingStyle.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class StoredDocument;
}

namespace SuperGameTools
{
    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// </summary>f
    class ToolsUniversalTemplate : public virtual UniversalObjectDataTemplate
    {
    public:

        ToolsUniversalTemplate(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode);

        /// <summary>
        /// Determines if this template is the one to use.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means this template is correct. </returns>
        virtual bool ShouldUseTemplate(const std::string& filepath) const override;

        /// <summary>
        /// Create a universal object data file based on the file path.
        /// </summary>
        /// <param name="filepath">Filepath to use as a base. </param>
        /// <returns>An universal object data file </returns>
        virtual std::string CreateBaseFile(const std::string& filepath) const override;

        /// <summary>
        /// Gets the file type to create when creating a <see cref="UniversalObjectData"/> file type.
        /// <see cref="UniversalObjectDataFileType::Unknown"/> means there is none set and the default should be used.
        /// This is very general and there tend to be more specific types at higher levels.
        /// </summary>
        /// <returns>The file type to be created. </returns>
        virtual UniversalObjectDataFileType GetUniversalObjectDataFileType() const override;

    private:
        /// <summary>
        /// Describes how a template might figure out if a given file is in fact the template
        /// for which it is defined. For instance does the file path make a match.
        /// </summary>
        UniversalObjectDataTemplateMatchingStyle m_matchingStyle;

        /// <summary>
        /// In some matching criteria the extensions are how a template is matched to the date it relates.
        /// </summary>
        std::unordered_set<std::string> m_matchingExtensions;

        /// <summary>
        /// The file type to create when creating a <see cref="UniverObjectData"/> file.
        /// <see cref="UniversalObjectDataFileType::Unknown"/> means there is none set and the default should be used.
        /// </summary>
        UniversalObjectDataFileType m_universalObjectDataFileType;;

        /// <summary>
        /// The method used to create a brand-new Universal Object Data file.
        /// </summary>
        UniversalObjectDataTemplateCreationMethod m_creationMethod;

        /// <summary>
        /// The empty document to use when recreating the Universal Object Data file.
        /// </summary>
        std::string m_creationDocumentCopy;

#pragma region Root Parsing

        /// <summary>
        /// Parses the root node attributes.
        /// </summary>
        /// <param name="rootNode">Root template node.</param>
        void ParseRootAttributes(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& rootNode);

#pragma endregion

#pragma region Matching Criteria Creation

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

#pragma endregion
#pragma region Should Use Template

        /// <summary>
        /// Should use template logic when extension is selected.
        /// </summary>
        /// <param name="filepath">Filepath of the original file. </param>
        /// <returns>True means should use template. </returns>
        bool ShouldUseTemplateExtension(const std::string& filepath) const;

#pragma endregion

#pragma region CreateUODFile Creation

        /// <summary>
        /// Creates the data for the Template node which allows us to create Universal Object Data files.
        /// </summary>
        /// <param name="templateNode">The Template node. </param>
        void CreateDataForCreateUniversalObjectDataFile(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& templateNode);

        /// <summary>
        /// Creates the data for the Template node which allows us to create Universal Object Data files.
        /// This is the logic for simple creation.
        /// </summary>
        /// <param name="templateNode">The Template node. </param>
        void CreateDataForCreateUniversalObjectDataFileSimple(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& templateNode);

#pragma endregion

#pragma region CreateUODFile
        /// <summary>
        /// Create an Universal Object Data file based on the file path using the simple logic.
        /// </summary>
        /// <param name="filepath">Filepath to use as a base. </param>
        /// <returns>An Universal Object Data file </returns>
        virtual std::string CreateUniversalObjectDataFileSimple(const std::string& filepath) const;

#pragma endregion
    };
}
