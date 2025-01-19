#include "TreeViewItem.h"

#include "TreeViewItemOnSelectedEventArguments.h"
#include "../../../ImGuiIncludes.h"
#include "../../../../Engine/Engine/Content/ContentManager.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

TreeViewItem::TreeViewItem(const std::shared_ptr<ContentManager>& contentManager)
{
    m_guid = GUIDHelpers::CreateGUID();
    m_label = std::make_shared<ValueProperty<std::string>>(
        "Label", "Empty");
    m_children = std::make_shared<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>>(
        "Children", std::vector<std::shared_ptr<TreeViewItem>>());
    
    m_treeViewItemCollapsibleBehaviour = std::make_shared<ValueProperty<TreeViewItemCollapsibleBehaviour>>(
        "CollapsibleType", TreeViewItemCollapsibleBehaviour::CanOpenClose);
    m_treeViewItemCollapsibleIcon = std::make_shared<ValueProperty<TreeViewItemCollapsibleIcon>>(
        "CollapsibleIcon", TreeViewItemCollapsibleIcon::Arrow);

    m_isOpen = std::make_shared<ValueProperty<bool>>("IsOpen", false);
    m_isSelected = std::make_shared<ValueProperty<bool>>("IsSelected", false);
    m_openOnStart = std::make_shared<ValueProperty<bool>>("OpenOnStart", false);
    m_isFramed = std::make_shared<ValueProperty<bool>>("IsFramed", false);
    m_shouldRender = std::make_shared<ValueProperty<bool>>("ShouldRender", true);

    m_onSelectedEvent = std::make_shared<FEvent>();

    const std::string methodName = "TreeView::TreeView(std::shared_ptr<ContentManager>, std::shared_ptr<TreeViewItem>)";
    if (!contentManager)
    {
        Log::Error("No content manager given.", methodName);
        return;
    }

    if (!contentManager->Texture())
    {
        Log::Error("No texture manager given.", methodName);
        return;
    }

    m_upArrow = contentManager->Texture()->GetTexture("Tools\\Icons\\TreeArrowUp\\TreeArrowUp.png");
    if (!m_upArrow)
    {
        Log::Error("Could not load up arrow.", methodName);
    }
    m_downArrow = contentManager->Texture()->GetTexture("Tools\\Icons\\TreeArrowDown\\TreeArrowDown.png");
    if (!m_downArrow)
    {
        Log::Error("Could not load down arrow.", methodName);
    }

    m_arrowSize = ImVec2(13, 13);
}

std::shared_ptr<Guid> TreeViewItem::GetUniqueID() const
{
    return m_guid;
}

void TreeViewItem::OnPropertyChanged(const std::string& name)
{
}

std::shared_ptr<ValueProperty<std::string>> TreeViewItem::GetLabel() const
{
    return m_label;
}

std::shared_ptr<ValueProperty<bool>> TreeViewItem::GetIsFramed() const
{
    return m_isFramed;
}

std::shared_ptr<ValueProperty<bool>> TreeViewItem::GetShouldRender() const
{
    return m_shouldRender;
}

std::shared_ptr<ValueProperty<bool>> TreeViewItem::GetOpenOnLoad() const
{
    return m_openOnStart;
}

std::shared_ptr<ValueProperty<TreeViewItemCollapsibleBehaviour>> TreeViewItem::GetCollapsibleType() const
{
    return m_treeViewItemCollapsibleBehaviour;
}

std::shared_ptr<ValueProperty<TreeViewItemCollapsibleIcon>> TreeViewItem::GetCollapsibleIcon() const
{
    return m_treeViewItemCollapsibleIcon;
}

std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>> TreeViewItem::GetChildren() const
{
    return m_children;
}

std::shared_ptr<ValueProperty<bool>> TreeViewItem::GetIsOpen() const
{
    return m_isOpen;
}

std::shared_ptr<ValueProperty<bool>> TreeViewItem::GetIsSelected() const
{
    return m_isSelected;
}

std::shared_ptr<FEvent> TreeViewItem::OnSelected()
{
    return m_onSelectedEvent;
}

void TreeViewItem::Draw()
{
    ImVec2 position = ImGui::GetCursorPos();

    bool alwaysOpen = GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::AlwaysShown;
    if (!alwaysOpen && GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::Arrow &&
        GetCollapsibleType()->GetValue() != TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly)
    {
        RenderSelectableArrow(position);
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
    }

    if (GetIsFramed()->GetValue())
    {
        RenderFullBackground(position);
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
    }

    RenderSelectableRow(position);
    ImGui::SetCursorPos(ImVec2(position.x, position.y));

    if (GetCollapsibleIcon()->GetValue() == TreeViewItemCollapsibleIcon::Arrow)
    {
        RenderArrowImage(position);
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
    }

    RenderRowText(position);
    ImGui::SetCursorPos(ImVec2(position.x, position.y));
}

void TreeViewItem::RenderSelectableArrow(ImVec2 originalPosition) const
{
    bool imageIsHovered = false;
    bool image_selected = GetIsOpen()->GetValue();
    if (ImGui::InvisibleButton("##image_invisible", m_arrowSize))
    {
        image_selected = !image_selected;
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_None))
        {
            // TODO: Add Arrow hover image for Scene Hierarchy #110
            imageIsHovered = true;
        }
    }

    GetIsOpen()->SetValue(image_selected);
}

void TreeViewItem::RenderFullBackground(ImVec2 originalPosition) const
{
    // This draws a background under all the elements.
    // The numbers are just keyed in to perfectly align.

    ImVec2 topLeft = ImGui::GetCursorScreenPos();
    topLeft.y -= 2;
    topLeft.x -= 4;

    float width = ImGui::GetContentRegionAvail().x + 8;
    float height = 22;

    // TODO: Create colour scheme for all ImGui and UX scheme #109
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(topLeft, ImVec2(topLeft.x + width, topLeft.y + height), IM_COL32(33, 11, 197, 255));
}

void TreeViewItem::RenderSelectableRow(ImVec2 originalPosition)
{
    // Default 'header' is for selected.
    // TODO: Create colour scheme for all ImGui and UX scheme #109
    ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(43, 77, 232, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32(37, 68, 221, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, IM_COL32(83, 105, 238, 255));

    bool isSelected = GetIsSelected()->GetValue();
    if (ImGui::Selectable("##Selectable", isSelected, ImGuiSelectableFlags_AllowDoubleClick))
    {
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) &&
            (GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::CanOpenClose ||
                GetCollapsibleType()->GetValue() == TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly))
        {
            GetIsOpen()->SetValue(!GetIsOpen()->GetValue());
        }
        else
        {
            isSelected = !isSelected;
            if (isSelected)
            {
                auto arguments = std::make_shared
                    <TreeViewItemOnSelectedEventArguments>(
                        TreeViewItem::GetWeakDistributed());
                OnSelected()->Invoke(arguments);
            }
        }
    }
    GetIsSelected()->SetValue(isSelected);

    ImGui::PopStyleColor(3);
}

void TreeViewItem::RenderArrowImage(ImVec2 originalPosition) const
{
    // TODO: Create colour scheme for all ImGui and UX scheme #109
    if (GetIsOpen()->GetValue())
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

void TreeViewItem::RenderRowText(ImVec2 originalPosition) const
{
    // This renders the text on top of the entire row.
    // We need to ensure that we do not overlap the image when we do.

    int leftPadding = 3;
    int offsetX = static_cast<int>(static_cast<int>(m_arrowSize.x) + leftPadding);

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(241, 235, 109, 255));
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + static_cast<float>(offsetX));
    ImGui::Text(GetLabel()->GetValue().c_str());
    ImGui::PopStyleColor();
}

