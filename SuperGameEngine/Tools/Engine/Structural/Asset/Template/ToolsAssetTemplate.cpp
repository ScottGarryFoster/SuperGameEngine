#include "ToolsAssetTemplate.h"

#include "AssetTemplateCreationMethod.h"
#include "AssetTemplateMatchingStyle.h"
#include "../../../../FatedQuestLibraries.h"
#include "Engine/Structural/Asset/AssetFiles/AssetFileType.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_matchingStyle = AssetTemplateMatchingStyle::Unknown;
    m_creationMethod = AssetTemplateCreationMethod::Unknown;
    m_assetFileType = AssetFileType::Unknown;
    m_creationDocumentCopy = {};

    ParseRootAttributes(documentNode);
    for (std::shared_ptr<StoredDocumentNode> current = documentNode->GetFirstChild(); current; current = current->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(current->Name());
        if (m_matchingStyle == AssetTemplateMatchingStyle::Unknown && nodeName == "matchingcriteria")
        {
            CreateDataForMatchingCriteria(current);
        }

        if (m_creationMethod == AssetTemplateCreationMethod::Unknown && nodeName == "template")
        {
            CreateDataForCreateAssetFile(current);
        }
    }

    if (m_matchingStyle == AssetTemplateMatchingStyle::Unknown)
    {
        Log::Error("AssetTemplateMatchingStyle Could not be parsed or found. This asset type will never be matched.", 
            "ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<StoredDocumentNode>");
    }

    if (m_creationMethod == AssetTemplateCreationMethod::Unknown)
    {
        Log::Error("AssetTemplateCreationMethod Could not be parsed or found. This asset type will never be created.",
            "ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<StoredDocumentNode>");
    }
}

ToolsAssetTemplate::~ToolsAssetTemplate()
{
}

bool ToolsAssetTemplate::ShouldUseTemplate(const std::string& filepath) const
{
    // Cannot use if there is no way to create.
    if (m_creationMethod == AssetTemplateCreationMethod::Unknown)
    {
        return false;
    }

    switch (m_matchingStyle)
    {
    case AssetTemplateMatchingStyle::Extension:
        return ShouldUseTemplateExtension(filepath);
    }

    return false;
}

std::string ToolsAssetTemplate::CreateAssetFile(const std::string& filepath) const
{
    switch (m_creationMethod)
    {
    case AssetTemplateCreationMethod::Simple:
        return CreateAssetFileSimple(filepath);
    }

    return {};
}

AssetFileType ToolsAssetTemplate::GetAssetFileType() const
{
    return m_assetFileType;
}

void ToolsAssetTemplate::ParseRootAttributes(
    const std::shared_ptr<StoredDocumentNode>& rootNode)
{
    if (auto assetFileAttribute = 
        rootNode->Attribute("assetfiletype", CaseSensitivity::IgnoreCase))
    {
        m_assetFileType = EAssetFileType::FromString(assetFileAttribute->Value());
        if (m_assetFileType == AssetFileType::Unknown)
        {
            Log::Error("Could not parse AssetFileType in template, "
                       "please ensure it is added Tools side. Value: " + assetFileAttribute->Value(),
                "ToolsAssetTemplate::ParseRootAttributes(const std::shared_ptr<StoredDocumentNode>&)");
        }
    }
}

void ToolsAssetTemplate::CreateDataForMatchingCriteria(
    const std::shared_ptr<StoredDocumentNode>& matchingNodeRoot)
{

    if (std::shared_ptr<StoredDocumentAttribute> matchingStyleAttribute = 
        matchingNodeRoot->Attribute("AssetTemplateMatchingStyle", CaseSensitivity::IgnoreCase))
    {
        m_matchingStyle = EAssetTemplateMatchingStyle::FromString(matchingStyleAttribute->Value(), false);
    }

    // No point continuing if we have no matching point style.
    if (m_matchingStyle == AssetTemplateMatchingStyle::Unknown)
    {
        return;
    }

    switch (m_matchingStyle)
    {
    case AssetTemplateMatchingStyle::Extension:
        CreateDataForMatchingCriteriaExtension(matchingNodeRoot);
        break;

    default:
        Log::Error("Case not implemented for AssetTemplateMatchingStyle. Value: " + 
            EAssetTemplateMatchingStyle::ToString(m_matchingStyle), 
            "ToolsAssetTemplate::CreateDataForMatchingCriteria(const std::shared_ptr<StoredDocumentNode>&)");
    }
}

void ToolsAssetTemplate::CreateDataForMatchingCriteriaExtension(
    const std::shared_ptr<StoredDocumentNode>& matchingNodeRoot)
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

bool ToolsAssetTemplate::ShouldUseTemplateExtension(const std::string& filepath) const
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

void ToolsAssetTemplate::CreateDataForCreateAssetFile(
    const std::shared_ptr<StoredDocumentNode>& templateNode)
{
    if (std::shared_ptr<StoredDocumentAttribute> matchingStyleAttribute =
        templateNode->Attribute("AssetTemplateCreationMethod", CaseSensitivity::IgnoreCase))
    {
        m_creationMethod = EAssetTemplateCreationMethod::FromString(matchingStyleAttribute->Value(), false);
    }

    // No point continuing if we have no creation method.
    if (m_creationMethod == AssetTemplateCreationMethod::Unknown)
    {
        return;
    }

    switch (m_creationMethod)
    {
    case AssetTemplateCreationMethod::Simple:
        CreateDataForCreateAssetFileSimple(templateNode);
        break;
    default:
        Log::Error("Case not implemented for AssetTemplateCreationMethod. Value: " +
            EAssetTemplateCreationMethod::ToString(m_creationMethod),
            "ToolsAssetTemplate::CreateDataForCreateAssetFile(const std::shared_ptr<StoredDocumentNode>&)");
    }
}

void ToolsAssetTemplate::CreateDataForCreateAssetFileSimple(
    const std::shared_ptr<StoredDocumentNode>& templateNode)
{
    std::shared_ptr<StoredDocumentNode> firstChild = templateNode->GetFirstChild();
    if (!firstChild)
    {
        Log::Error("No child of template found therefore no asset file contents found.",
            "ToolsAssetTemplate::CreateDataForCreateAssetFileSimple(const std::shared_ptr<StoredDocumentNode>&)");
        return;
    }

    auto templateDocument = std::make_shared<ModifiableDocument>();
    if (!templateDocument->Load(firstChild))
    {
        Log::Error("Could not load asset file from the first child of template.",
            "ToolsAssetTemplate::CreateDataForCreateAssetFileSimple(const std::shared_ptr<StoredDocumentNode>&)");
        return;
    }

    std::shared_ptr<DocumentToXml> documentToXml = std::make_shared<SimpleDocumentToXml>();
    m_creationDocumentCopy = documentToXml->ConvertToXml(templateDocument);
    if (m_creationDocumentCopy.empty())
    {
        Log::Error("Could not convert the asset template into a simple string.",
            "ToolsAssetTemplate::CreateDataForCreateAssetFileSimple(const std::shared_ptr<StoredDocumentNode>&)");
        return;
    }
}

std::string ToolsAssetTemplate::CreateAssetFileSimple(const std::string& filepath) const
{
    // Can use StringHelpers::ReplaceAll here in future commit
    std::string displayName = File::GetFilename(filepath);
    displayName = File::RemoveAllExtensions(displayName);
    displayName = StringHelpers::DisplayName(displayName);

    std::string copy = StringHelpers::ReplaceAll(m_creationDocumentCopy, "{FilepathDisplayName}", displayName);

    return copy;
}
