#pragma once
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"

namespace SuperGameTools
{
    class ComponentTreeViewItem;

    /// <summary>
    /// Renders a Component in the inspector
    /// </summary>
    class ComponentTreeViewHeaderItem : public TreeViewItem
    {
    public:
        ComponentTreeViewHeaderItem(const std::shared_ptr<ContentManager>& contentManager);

        /// <summary>
        /// Children of this tree view item.
        /// </summary>
        /// <returns>Children of this tree view item. </returns>
        virtual std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>> GetChildrenAsComponents() const;

        /// <summary>
        /// Children as not automatically updated.
        /// When the list itself is updated, call this to trigger the update.
        /// </summary>
        void UpdateChildren() const;

    private:
        /// <summary>
        /// The component this item manages.
        /// </summary>
        std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>> m_childrenAsTreeViewItems;
    };
}
