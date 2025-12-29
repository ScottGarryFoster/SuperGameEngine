#include "ToolsUniversalMetaData.h"

#include "SingleToolsUniversalLayout.h"
#include "../../../../FatedQuest.Libraries/Exceptions/AllReferences.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "Engine/Structural/Asset/Template/ToolsAssetTemplate.h"

using namespace FatedQuestLibraries;

SuperGameTools::ToolsUniversalMetaData::ToolsUniversalMetaData(
    const std::shared_ptr<FatedQuestLibraries::StoredDocument>& document,
    const std::shared_ptr<LayoutEditorFactory>& layoutFactory)
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
            // TODO: This should make a non-asset template.
            m_template = std::make_shared<ToolsAssetTemplate>(current);
        }

        if (!m_layout && nodeName == "layout")
        {
            m_layout = std::make_shared<SingleToolsUniversalLayout>(current, layoutFactory);
        }
    }
}

std::shared_ptr<SuperGameTools::UniversalTemplate> SuperGameTools::ToolsUniversalMetaData::GetTemplate() const
{
    return m_template;
}

std::shared_ptr<SuperGameTools::SingleLayout> SuperGameTools::ToolsUniversalMetaData::GetLayout() const
{
    return m_layout;
}
