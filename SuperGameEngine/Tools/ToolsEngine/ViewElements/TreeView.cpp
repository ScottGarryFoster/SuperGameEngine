#include "TreeView.h"
#include "TreeViewItem.h"
#include "../../ImGuiIncludes.h"

#include <string>

using namespace SuperGameTools;

TreeView::TreeView(const std::shared_ptr<TreeViewItem>& treeViewItem)
{
    m_treeViewItemRoot = treeViewItem;
    m_shouldRootBeFramed = false;
    m_indentationDepth = 0;
}

void TreeView::Draw() const
{
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 9.0f);
    RenderItem(m_treeViewItemRoot, true, 0);
    ImGui::PopStyleVar();
}

void TreeView::ShouldRootBeFrame(bool shouldRootBeFrame)
{
    m_shouldRootBeFramed = shouldRootBeFrame;
}

void TreeView::SetDepthToStartIndentation(int depth)
{
    m_indentationDepth = depth < 0 ? 0 : depth;
}

void TreeView::RenderItem(const std::shared_ptr<TreeViewItem>& current, bool isRoot, int depth) const
{
    ImGui::PushID(current->GetUniqueID()->ToString().c_str());

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
    if (current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly)
    {
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;
    }
    else if (current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly)
    {
        flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
    }
    else if (current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::CanOpenClose)
    {
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    }
    else
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (current->GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::Bullet)
    {
        flags |= ImGuiTreeNodeFlags_Bullet;
    }
    else if (current->GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::NoIcon)
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (isRoot && m_shouldRootBeFramed)
    {
        flags |= ImGuiTreeNodeFlags_Framed;
    }

    if (depth > m_indentationDepth)
    {
        ImGui::Indent();
    }

    // If the user does not want any icon, then render with a selectable instead.
    if (current->GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::NoIcon && 
        current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::CanOpenClose)
    {
        bool isOpen = current->GetIsOpen()->GetValue();
        if (ImGui::Selectable(current->GetLabel()->GetValue().c_str(), isOpen, {}))
        {
            isOpen = !isOpen;
        }

        if (isOpen)
        {
            for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
            {
                RenderItem(child, false, depth + 1);
            }
        }

        current->GetIsOpen()->SetValue(isOpen);
    }
    else
    {
        // Otherwise use the tree.
        if (ImGui::TreeNodeEx(current->GetLabel()->GetValue().c_str(), flags))
        {
            for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
            {
                RenderItem(child, false, depth + 1);
            }
        }
    }

    if (depth > m_indentationDepth)
    {
        ImGui::Unindent();
    }

    ImGui::PopID();
}
