#include "ToolsUniversalTemplate.h"
#include "../../../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../../../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "../../../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsUniversalTemplate::ToolsUniversalTemplate(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_matchingStyle = UniversalObjectDataTemplateMatchingStyle::Unknown;
    m_creationMethod = UniversalObjectDataTemplateCreationMethod::Unknown;
    m_universalObjectDataFileType = UniversalObjectDataFileType::Unknown;
    m_creationDocumentCopy = {};

    ParseRootAttributes(documentNode);
    for (std::shared_ptr<StoredDocumentNode> current = documentNode->GetFirstChild(); current; current = current->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(current->Name());
        if (m_matchingStyle == UniversalObjectDataTemplateMatchingStyle::Unknown && nodeName == "matchingcriteria")
        {
            CreateDataForMatchingCriteria(current);
        }

        if (m_creationMethod == UniversalObjectDataTemplateCreationMethod::Unknown && nodeName == "template")
        {
            CreateDataForCreateUniversalObjectDataFile(current);
        }
    }

    if (m_matchingStyle == UniversalObjectDataTemplateMatchingStyle::Unknown)
    {
        Log::Error("UniversalObjectDataTemplateMatchingStyle Could not be parsed or found. This file type will never be matched.",
            "ToolsUniversalTemplate::ToolsUniversalTemplate(const std::shared_ptr<StoredDocumentNode>");
    }

    if (m_creationMethod == UniversalObjectDataTemplateCreationMethod::Unknown)
    {
        Log::Error("UniversalObjectDataTemplateCreationMethod Could not be parsed or found. This file type will never be created.",
            "ToolsUniversalTemplate::ToolsUniversalTemplate(const std::shared_ptr<StoredDocumentNode>");
    }
}

bool ToolsUniversalTemplate::ShouldUseTemplate(const std::string& filepath) const
{
    // Cannot use if there is no way to create.
    if (m_creationMethod == UniversalObjectDataTemplateCreationMethod::Unknown)
    {
        return false;
    }

    switch (m_matchingStyle)
    {
    case UniversalObjectDataTemplateMatchingStyle::Extension:
        return ShouldUseTemplateExtension(filepath);
    }

    return false;
}

std::string ToolsUniversalTemplate::CreateBaseFile(const std::string& filepath) const
{
    switch (m_creationMethod)
    {
    case UniversalObjectDataTemplateCreationMethod::Simple:
        return CreateUniversalObjectDataFileSimple(filepath);
    }

    return {};
}

UniversalObjectDataFileType ToolsUniversalTemplate::GetUniversalObjectDataFileType() const
{
    return m_universalObjectDataFileType;
}

void ToolsUniversalTemplate::ParseRootAttributes(const std::shared_ptr<StoredDocumentNode>& rootNode)
{
    if (auto fileAttribute =
        rootNode->Attribute("UniversalObjectDataFileType", CaseSensitivity::IgnoreCase))
    {
        m_universalObjectDataFileType = EUniversalObjectDataFileType::FromString(fileAttribute->Value());
        if (m_universalObjectDataFileType == UniversalObjectDataFileType::Unknown)
        {
            Log::Error("Could not parse UniversalObjectDataFileType in template, "
                "please ensure it is added Tools side. Value: " + fileAttribute->Value(),
                "ToolsUniversalTemplate::ParseRootAttributes(const std::shared_ptr<StoredDocumentNode>&)");
        }
    }
    else
    {
        // Adding a UOD File type is entirely optional for this type, it is almost always a game asset.
        m_universalObjectDataFileType = UniversalObjectDataFileType::GameAsset;
    }
}

void ToolsUniversalTemplate::CreateDataForMatchingCriteria(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& matchingNodeRoot)
{
    if (std::shared_ptr<StoredDocumentAttribute> matchingStyleAttribute =
        matchingNodeRoot->Attribute("UniversalObjectDataTemplateMatchingStyle", CaseSensitivity::IgnoreCase))
    {
        m_matchingStyle = EUniversalObjectDataTemplateMatchingStyle::FromString(matchingStyleAttribute->Value(), false);
    }

    // No point continuing if we have no matching point style.
    if (m_matchingStyle == UniversalObjectDataTemplateMatchingStyle::Unknown)
    {
        return;
    }

    switch (m_matchingStyle)
    {
    case UniversalObjectDataTemplateMatchingStyle::Extension:
        CreateDataForMatchingCriteriaExtension(matchingNodeRoot);
        break;

    default:
        Log::Error("Case not implemented for UniversalObjectDataTemplateMatchingStyle. Value: " +
            EUniversalObjectDataTemplateMatchingStyle::ToString(m_matchingStyle),
            "ToolsUniversalTemplate::CreateDataForMatchingCriteria(const std::shared_ptr<StoredDocumentNode>&)");
    }
}

void ToolsUniversalTemplate::CreateDataForMatchingCriteriaExtension(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& matchingNodeRoot)
{
    std::shared_ptr<StoredDocumentNode> root = matchingNodeRoot;
    for (std::shared_ptr<StoredDocumentNode> current = root->GetFirstChild(); current; current = current->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(current->Name());
        if (nodeName == "extension")
        {
            if (std::shared_ptr<StoredDocumentAttribute> valueAttribute =
                current->Attribute("value", CaseSensitivity::IgnoreCase))
            {
                if (valueAttribute->Value().empty())
                {
                    continue;
                }

                // Ensure we store the extension in a lower case form.
                m_matchingExtensions.insert(StringHelpers::ToLower(valueAttribute->Value()));
            }
        }
    }
}

bool ToolsUniversalTemplate::ShouldUseTemplateExtension(const std::string& filepath) const
{
    std::string extension = File::GetExtension(filepath);
    if (StringHelpers::Equals(extension, ".ast", CaseSensitivity::IgnoreCase))
    {
        std::string filePathWithOneLessExtension = File::RemoveLastExtension(filepath);
        extension = File::GetExtension(filePathWithOneLessExtension);
    }

    if (extension.empty())
    {
        return false;
    }

    extension = StringHelpers::ToLower(extension);
    return m_matchingExtensions.contains(extension);
}

void ToolsUniversalTemplate::CreateDataForCreateUniversalObjectDataFile(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& templateNode)
{
    if (std::shared_ptr<StoredDocumentAttribute> matchingStyleAttribute =
        templateNode->Attribute("UniversalObjectDataTemplateCreationMethod", CaseSensitivity::IgnoreCase))
    {
        m_creationMethod = EUniversalObjectDataTemplateCreationMethod::FromString(matchingStyleAttribute->Value(), false);
    }

    // No point continuing if we have no creation method.
    if (m_creationMethod == UniversalObjectDataTemplateCreationMethod::Unknown)
    {
        return;
    }

    switch (m_creationMethod)
    {
    case UniversalObjectDataTemplateCreationMethod::Simple:
        CreateDataForCreateUniversalObjectDataFileSimple(templateNode);
        break;
    default:
        Log::Error("Case not implemented for UniversalObjectDataTemplateCreationMethod. Value: " +
            EUniversalObjectDataTemplateCreationMethod::ToString(m_creationMethod),
            "ToolsUniversalTemplate::CreateDataForCreateUniversalObjectDataFile(const std::shared_ptr<StoredDocumentNode>&)");
    }
}

void ToolsUniversalTemplate::CreateDataForCreateUniversalObjectDataFileSimple(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& templateNode)
{
    std::shared_ptr<StoredDocumentNode> firstChild = templateNode->GetFirstChild();
    if (!firstChild)
    {
        Log::Error("No child of template found therefore no file contents found.",
            "ToolsUniversalTemplate::CreateDataForCreateUniversalObjectDataFileSimple(const std::shared_ptr<StoredDocumentNode>&)");
        return;
    }

    auto templateDocument = std::make_shared<ModifiableDocument>();
    if (!templateDocument->Load(firstChild))
    {
        Log::Error("Could not load file from the first child of template.",
            "ToolsUniversalTemplate::CreateDataForCreateUniversalObjectDataFileSimple(const std::shared_ptr<StoredDocumentNode>&)");
        return;
    }

    std::shared_ptr<DocumentToXml> documentToXml = std::make_shared<SimpleDocumentToXml>();
    m_creationDocumentCopy = documentToXml->ConvertToXml(templateDocument);
    if (m_creationDocumentCopy.empty())
    {
        Log::Error("Could not convert the template into a simple string.",
            "ToolsUniversalTemplate::CreateDataForCreateUniversalObjectDataFileSimple(const std::shared_ptr<StoredDocumentNode>&)");
        return;
    }
}

std::string ToolsUniversalTemplate::CreateUniversalObjectDataFileSimple(const std::string& filepath) const
{
    // Can use StringHelpers::ReplaceAll here in future commit
    std::string displayName = File::GetFilename(filepath);
    displayName = File::RemoveAllExtensions(displayName);
    displayName = StringHelpers::DisplayName(displayName);

    std::string copy = StringHelpers::ReplaceAll(m_creationDocumentCopy, "{FilepathDisplayName}", displayName);

    return copy;
}
