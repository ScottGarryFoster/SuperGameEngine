#include "TreeView.h"
#include "TreeViewItem.h"
#include "../../../ImGuiIncludes.h"

#include <string>

#include "TreeViewItemOnSelectedEventArguments.h"
#include "../../../../Engine/Engine/Content/ContentManager.h"

using namespace SuperGameTools;

TreeView::TreeView(
    const std::shared_ptr<ContentManager>& contentManager,
    const std::shared_ptr<TreeViewItem>& treeViewItem)
{
    m_contentManager = contentManager;
    m_treeViewItemRoot = treeViewItem;
    m_shouldRootBeFramed = false;
    m_indentationDepth = 0;
    m_arrowSize = ImVec2(13, 13);
    m_haveSetup = false;

    const std::string methodName = "TreeView::TreeView(std::shared_ptr<ContentManager>, std::shared_ptr<TreeViewItem>)";
    if (!m_contentManager)
    {
        Log::Error("No content manager given.", methodName);
        return;
    }

    if (!m_contentManager->Texture())
    {
        Log::Error("No texture manager given.", methodName);
        return;
    }

    m_upArrow = m_contentManager->Texture()->GetTexture("Tools\\Icons\\TreeArrowUp\\TreeArrowUp.png");
    if (!m_upArrow)
    {
        Log::Error("Could not load up arrow.", methodName);
    }
    m_downArrow = m_contentManager->Texture()->GetTexture("Tools\\Icons\\TreeArrowDown\\TreeArrowDown.png");
    if (!m_downArrow)
    {
        Log::Error("Could not load down arrow.", methodName);
    }
}

void TreeView::Update()
{
    if (!m_haveSetup)
    {
        Setup();
        m_haveSetup = true;
    }
}

void TreeView::Draw() const
{
    if (!m_haveSetup)
    {
        return;
    }

    RenderItem(m_treeViewItemRoot, 0);
}

void TreeView::ShouldRootBeFrame(bool shouldRootBeFrame)
{
    m_shouldRootBeFramed = shouldRootBeFrame;
}

void TreeView::SetDepthToStartIndentation(int depth)
{
    m_indentationDepth = depth < 0 ? 0 : depth;
}

std::shared_ptr<TreeViewItem> TreeView::GetRootItem() const
{
    return m_treeViewItemRoot;
}

void TreeView::Setup()
{
    SetAnyDefaultsAsActuals(m_treeViewItemRoot, 0);
}

void TreeView::SetAnyDefaultsAsActuals(const std::shared_ptr<TreeViewItem>& current, int depth) const
{
    if (current->GetOpenOnLoad()->GetValue())
    {
        current->GetIsOpen()->SetValue(true);
    }

    for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
    {
        SetAnyDefaultsAsActuals(child, depth + 1);
    }
}

void TreeView::RenderItem(const std::shared_ptr<TreeViewItem>& current, int depth) const
{
    ImGui::PushID(current->GetUniqueID().get());

    bool shouldRender = current->GetShouldRender()->GetValue();
    if (depth > m_indentationDepth && shouldRender)
    {
        ImGui::Indent();
    }

    if (shouldRender)
    {
        ImGui::BeginGroup();
        current->Draw();
        ImGui::EndGroup();
    }

    bool isOpen =
        current->GetIsOpen()->GetValue() ||
        current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::AlwaysShown;
    if (isOpen)
    {
        if (shouldRender)
        {
            ++depth;
        }
        for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
        {
            RenderItem(child, depth);
        }
    }

    if (depth > m_indentationDepth && shouldRender)
    {
        ImGui::Unindent();
    }

    ImGui::PopID();
}
