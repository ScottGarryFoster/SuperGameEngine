#include "TreeViewItem.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

TreeViewItem::TreeViewItem()
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

