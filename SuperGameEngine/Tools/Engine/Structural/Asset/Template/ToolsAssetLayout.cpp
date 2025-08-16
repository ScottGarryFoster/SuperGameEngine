#include "ToolsAssetLayout.h"
#include "../../../../FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "Engine/Structural/Asset/LayoutEditors/AssetLayoutEditor.h"
#include "Engine/Structural/Asset/LayoutEditors/AssetLayoutEditorFactory.h"
#include "../../../../ImGuiIncludes.h"
#include "Imgui/External/imgui_internal.h"

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
    ImGui::BeginGroup();

    std::string id = "AssetLayout_" + universalObjectData->GetGuid()->ToString();
    ImGui::PushID(id.c_str());

    // TODO: Would like to do a better job of this table. See: [#184]
    if (ImGui::BeginTable("##MyTable", 2,
        ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings
    ))
    {
        ImVec2 table_size = ImGui::GetItemRectSize();

        ImGui::TableSetupColumn("##Column0",
            ImGuiTableColumnFlags_WidthFixed,
            m_sizeOfLeftColumn);

        ImGui::TableSetupColumn("##Column1",
            ImGuiTableColumnFlags_WidthStretch
            );

        for (const std::shared_ptr<const AssetLayoutEditor>& layout : m_assetLayoutEditor)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();

            float wrapX = ImGui::GetColumnOffset(0);
            
            ImGui::PushTextWrapPos(wrapX);
            layout->DrawLabel(universalObjectData);
            ImGui::PopTextWrapPos();

            ImGui::TableNextColumn();

            ImGui::PushItemWidth(-1);
            layout->DrawValue(universalObjectData);
            ImGui::PopItemWidth();
        }
        
        ImGui::EndTable();
    }

    ImGui::PopID();
    ImGui::EndGroup();


}

void ToolsAssetLayout::OnSave(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    for (const std::shared_ptr<const AssetLayoutEditor>& layout : m_assetLayoutEditor)
    {
        layout->OnSave(universalObjectData);
    }
}
