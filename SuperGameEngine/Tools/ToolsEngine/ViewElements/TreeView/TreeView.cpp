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

    if (depth > m_indentationDepth)
    {
        ImGui::Indent();
    }

    ImGui::BeginGroup();
    RenderRow(current, depth);
    ImGui::EndGroup();

    bool isOpen = 
        current->GetIsOpen()->GetValue() || 
        current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::AlwaysShown;
    if (isOpen)
    {
        for (const std::shared_ptr<TreeViewItem>& child : current->GetChildren()->GetValue())
        {
            RenderItem(child, depth + 1);
        }
    }

    if (depth > m_indentationDepth)
    {
        ImGui::Unindent();
    }

    ImGui::PopID();
}

void TreeView::RenderRow(const std::shared_ptr<TreeViewItem>& current, int depth) const
{
    ImVec2 position = ImGui::GetCursorPos();

    bool alwaysOpen = current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::AlwaysShown;
    if (!alwaysOpen && current->GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::Arrow &&
        current->GetCollapsibleType()->GetValue() != TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly)
    {
        RenderSelectableArrow(current, position);
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
    }

    if (depth <= 0 && m_shouldRootBeFramed)
    {
        RenderFullBackground(current, position);
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
    }

    RenderSelectableRow(current, position);
    ImGui::SetCursorPos(ImVec2(position.x, position.y));

    if (current->GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::Arrow)
    {
        RenderArrowImage(current, position);
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
    }

    RenderRowText(current, position);
    ImGui::SetCursorPos(ImVec2(position.x, position.y));
}

void TreeView::RenderSelectableArrow(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const
{
    bool imageIsHovered = false;
    bool image_selected = current->GetIsOpen()->GetValue();
    if (ImGui::InvisibleButton("##image_invisible", m_arrowSize))
    {
        image_selected = !image_selected;
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_None))
        {
            // TODO: Add Arrow hover image for Scene Hierarchy #110
            imageIsHovered = true;
        }
    }

    current->GetIsOpen()->SetValue(image_selected);
}

void TreeView::RenderFullBackground(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const
{
    // This draws a background under all the elements.
    // The numbers are just keyed in to perfectly align.

    ImVec2 topLeft = ImGui::GetCursorScreenPos();
    topLeft.y -= 2;
    topLeft.x -= 4;

    float width = ImGui::GetContentRegionAvail().x + 8;
    float height = 17.0f;

    // TODO: Create colour scheme for all ImGui and UX scheme #109
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(topLeft, ImVec2(topLeft.x + width, topLeft.y + height), IM_COL32(33, 11, 197, 255));
}

void TreeView::RenderSelectableRow(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const
{
    // Default 'header' is for selected.
    // TODO: Create colour scheme for all ImGui and UX scheme #109
    ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(43, 77, 232, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32(37, 68, 221, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, IM_COL32(83, 105, 238, 255));

    bool isSelected = current->GetIsSelected()->GetValue();
    if (ImGui::Selectable("##Selectable", isSelected, ImGuiSelectableFlags_AllowDoubleClick))
    {
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && 
            (current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::CanOpenClose || 
                current->GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly))
        {
            current->GetIsOpen()->SetValue(!current->GetIsOpen()->GetValue());
        }
        else
        {
            isSelected = !isSelected;
            if (isSelected)
            {
                auto arguments = std::make_shared<TreeViewItemOnSelectedEventArguments>(current);
                current->OnSelected()->Invoke(arguments);
            }
        }
    }
    current->GetIsSelected()->SetValue(isSelected);

    ImGui::PopStyleColor(3);
}

void TreeView::RenderArrowImage(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const
{
    // TODO: Create colour scheme for all ImGui and UX scheme #109
    if (current->GetIsOpen()->GetValue())
    {
        m_upArrow->Draw(FPoint(0, 1), 
            FPoint(static_cast<int>(m_arrowSize.x), static_cast<int>(m_arrowSize.y)));
    }
    else
    {
        m_downArrow->Draw(FPoint(0, 1), 
            FPoint(static_cast<int>(m_arrowSize.x), static_cast<int>(m_arrowSize.y)));
    }
}

void TreeView::RenderRowText(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const
{
    // This renders the text on top of the entire row.
    // We need to ensure that we do not overlap the image when we do.

    int leftPadding = 3; 
    int offsetX = static_cast<int>(static_cast<int>(m_arrowSize.x) + leftPadding);

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(241, 235, 109, 255));
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + static_cast<float>(offsetX));
    ImGui::Text(current->GetLabel()->GetValue().c_str());
    ImGui::PopStyleColor();
}
