#include "ComponentTreeViewHeaderItem.h"
#include "ComponentTreeViewItem.h"
#include <memory>
#include <vector>

using namespace SuperGameTools;

ComponentTreeViewHeaderItem::ComponentTreeViewHeaderItem(
    const std::shared_ptr<ContentManager>& contentManager) : TreeViewItem(contentManager)
{
    m_childrenAsTreeViewItems = std::make_shared<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>>
        ("ChildrenAsComponents", std::vector<std::shared_ptr<ComponentTreeViewItem>>());
}

std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>>
    ComponentTreeViewHeaderItem::GetChildrenAsComponents() const
{
    return m_childrenAsTreeViewItems;
}

void ComponentTreeViewHeaderItem::UpdateChildren() const
{
    std::vector<std::shared_ptr<TreeViewItem>> treeViewItems;
    for (const std::shared_ptr<ComponentTreeViewItem>& componentTreeViewItem
        : GetChildrenAsComponents()->GetValue())
    {
        treeViewItems.emplace_back(componentTreeViewItem);
    }

    GetChildren()->SetValue(treeViewItems);
}
