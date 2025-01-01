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

std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>> TreeViewItem::GetChildren() const
{
    return m_children;
}

