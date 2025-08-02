#include "ToolsAssetLayout.h"
#include "../../../../FatedQuestLibraries.h"
#include "Engine/Structural/Asset/LayoutEditors/AssetLayoutEditor.h"
#include "Engine/Structural/Asset/LayoutEditors/AssetLayoutEditorFactory.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetLayout::ToolsAssetLayout(
    const std::shared_ptr<StoredDocumentNode>& documentNode,
    const std::shared_ptr<AssetLayoutEditorFactory>& layoutFactory)
{
    if (!layoutFactory)
    {
        Log::Error("No factory given to Tools Asset Layout. Cannot read layouts.",
            "ToolsAssetLayout::ToolsAssetLayout("
            "const std::shared_ptr<StoredDocumentNode>&,"
            "const std::shared_ptr<AssetLayoutEditorFactory>&)");
        return;
    }

    std::shared_ptr<StoredDocumentNode> root = documentNode;
    for (std::shared_ptr<StoredDocumentNode> current = root->GetFirstChild(); current; current = current->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(current->Name());
        if (nodeName == "data")
        {
            std::shared_ptr<AssetLayoutEditor> layout = layoutFactory->Create(current);
            if (layout)
            {
                m_assetLayoutEditor.emplace_back(layout);
            }
            else
            {
                Log::Error("Failed to parse a layout data tag.",
                    "ToolsAssetLayout::ToolsAssetLayout("
                    "const std::shared_ptr<StoredDocumentNode>&,"
                    "const std::shared_ptr<AssetLayoutEditorFactory>&)");
            }
        }
    }
}

void ToolsAssetLayout::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    for (const std::shared_ptr<const AssetLayoutEditor>& layout : m_assetLayoutEditor)
    {
        layout->Update(universalObjectData);
    }
}

void ToolsAssetLayout::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    for (const std::shared_ptr<const AssetLayoutEditor>& layout : m_assetLayoutEditor)
    {
        layout->Draw(universalObjectData);
    }
}