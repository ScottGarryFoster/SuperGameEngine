#include "TreeView.h"
#include "TreeViewItem.h"
#include "../../ImGuiIncludes.h"

#include <string>

using namespace SuperGameTools;

TreeView::TreeView(const std::shared_ptr<TreeViewItem>& treeViewItem)
{
    m_treeViewItemRoot = treeViewItem;
    m_shouldRootBeFramed = false;
}

void TreeView::Draw() const
{
    RenderItem(m_treeViewItemRoot, true);
}

void TreeView::ShouldRootBeFrame(bool shouldRootBeFrame)
{
    m_shouldRootBeFramed = shouldRootBeFrame;
}

void TreeView::RenderItem(const std::shared_ptr<TreeViewItem>& current, bool isRoot) const
{
    ImGui::PushID(current->GetUniqueID()->ToString().c_str());

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    if (isRoot && m_shouldRootBeFramed)
    {
        flags |= ImGuiTreeNodeFlags_Framed;
    }

    if (ImGui::TreeNodeEx(current->GetLabel()->GetValue().c_str(), flags))
    {
        for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
        {
            RenderItem(child, false);
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
}
