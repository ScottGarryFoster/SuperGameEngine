#include "ToolsAssetMetaData.h"

#include "ToolsAssetLayout.h"
#include "ToolsAssetTemplate.h"
#include "../../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetMetaData::ToolsAssetMetaData(
    const std::shared_ptr<StoredDocument>& document)
{
    if (!document)
    {
        throw ArgumentNullException("Document must not be null");
    }

    if (!document->GetRoot())
    {
        throw DocumentInvalidException("Document must have a root node.");
    }

    std::shared_ptr<StoredDocumentNode> root = document->GetRoot();
    for (std::shared_ptr<StoredDocumentNode> current = root->GetFirstChild(); 
        current; 
        current = current->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(current->Name());
        if (!m_template && nodeName == "assettemplate")
        {
            m_template = std::make_shared<ToolsAssetTemplate>(current);
        }

        if (!m_layout && nodeName == "assetlayout")
        {
            m_layout = std::make_shared<ToolsAssetLayout>(current);
        }
    }
}

std::shared_ptr<AssetTemplate> ToolsAssetMetaData::GetTemplate() const
{
    return m_template;
}

std::shared_ptr<AssetLayout> ToolsAssetMetaData::GetLayout() const
{
    return m_layout;
}
