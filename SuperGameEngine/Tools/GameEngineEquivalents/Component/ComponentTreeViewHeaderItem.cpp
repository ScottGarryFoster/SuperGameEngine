#include "ComponentTreeViewHeaderItem.h"
#include "ComponentTreeViewItem.h"
#include <memory>
#include <vector>

#include "../../Windows/SceneHierarchy/EventArguments/OnMenuDeleteComponentEventArguments.h"

using namespace SuperGameTools;

ComponentTreeViewHeaderItem::ComponentTreeViewHeaderItem(
    const std::shared_ptr<ContentManager>& contentManager) : TreeViewItem(contentManager)
{
    m_childrenAsTreeViewItems = std::make_shared<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>>
        ("ChildrenAsComponents", std::vector<std::shared_ptr<ComponentTreeViewItem>>());

    m_onMenuDelete = std::make_shared<FEvent>();
}

std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>>
    ComponentTreeViewHeaderItem::GetChildrenAsComponents() const
{
    return m_childrenAsTreeViewItems;
}

std::shared_ptr<FEventSubscriptions> ComponentTreeViewHeaderItem::OnMenuDelete() const
{
    return m_onMenuDelete;
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

void ComponentTreeViewHeaderItem::DrawContextMenu()
{
    if (ImGui::BeginPopupContextItem("ComponentTreeViewHeaderItem-ContextMenu"))
    {
        bool canDelete = !GetChildrenAsComponents()->GetValue().empty();
        if (ImGui::MenuItem("Delete", nullptr, nullptr, canDelete))
        {
            std::shared_ptr<Component> component = GetChildrenAsComponents()->GetValue().at(0)->GetComponent();
            auto arguments = std::make_shared<OnMenuDeleteComponentEventArguments>(GetUniqueID(), component);
            m_onMenuDelete->Invoke(arguments);
        }

        ImGui::EndPopup();
    }
}