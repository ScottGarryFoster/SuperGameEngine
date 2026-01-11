#include "ToolsAssetTemplate.h"

#include "../../../../FatedQuestLibraries.h"
#include "Engine/Structural/Asset/AssetFiles/AssetFileType.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<StoredDocumentNode>& documentNode) : ToolsUniversalTemplate(documentNode)
{
    m_assetFileType = AssetFileType::Unknown;
    ParseRootAttributes(documentNode);
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