#include "ToolsAssetTemplate.h"

#include "AssetTemplateMatchingStyle.h"
#include "../../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_matchingStyle = AssetTemplateMatchingStyle::Unknown;

    std::shared_ptr<StoredDocumentNode> root = documentNode;
    for (std::shared_ptr<StoredDocumentNode> current = root->GetFirstChild(); current; current = current->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(current->Name());
        if (nodeName == "matchingcriteria")
        {
            CreateDataForMatchingCriteria(current);
        }
    }

    if (m_matchingStyle == AssetTemplateMatchingStyle::Unknown)
    {
        Log::Error("AssetTemplateMatchingStyle Could not be parsed or found. This asset will never be matched.", 
            "ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<StoredDocumentNode>");
    }
}

ToolsAssetTemplate::~ToolsAssetTemplate()
{
}

bool ToolsAssetTemplate::ShouldUseTemplate(const std::string& filepath) const
{
    switch (m_matchingStyle)
    {
    case AssetTemplateMatchingStyle::Extension:
        return ShouldUseTemplateExtension(filepath);
    }

    return false;
}

std::string ToolsAssetTemplate::CreateAssetFile(const std::string& filepath) const
{
    return std::string();
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
    if (extension.empty())
    {
        return false;
    }

    extension = StringHelpers::ToLower(extension);
    return m_matchingExtensions.contains(extension);
}