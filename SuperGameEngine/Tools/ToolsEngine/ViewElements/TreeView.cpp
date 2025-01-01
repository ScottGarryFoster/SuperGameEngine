#include "TreeView.h"
#include "TreeViewItem.h"
#include "../../ImGuiIncludes.h"

#include <string>

using namespace SuperGameTools;

TreeView::TreeView(const std::shared_ptr<TreeViewItem>& treeViewItem)
{
    m_treeViewItemRoot = treeViewItem;
}

void TreeView::Draw() const
{
    RenderItem(m_treeViewItemRoot);
}

void TreeView::RenderItem(const std::shared_ptr<TreeViewItem>& current) const
{
    ImGui::PushID(current->GetUniqueID()->ToString().c_str());

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    if (ImGui::TreeNodeEx(current->GetLabel()->GetValue().c_str(), flags))
    {
        for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
        {
            RenderItem(child);
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
}
