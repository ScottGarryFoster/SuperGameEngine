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
        /// Called when the user has requested to delete
        /// </summary>
        /// <returns>Called when the user has requested to delete. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnMenuDelete() const;

        /// <summary>
        /// Children as not automatically updated.
        /// When the list itself is updated, call this to trigger the update.
        /// </summary>
        void UpdateChildren() const;

    protected:
        /// <summary>
         /// Override with a context menu if there is one for this item in the tree view.
         /// </summary>
        virtual void DrawContextMenu() override;

    private:
        /// <summary>
        /// The component this item manages.
        /// </summary>
        std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<ComponentTreeViewItem>>>> m_childrenAsTreeViewItems;

        /// <summary>
        /// Called when the user has requested to delete.
        /// </summary>
        std::shared_ptr<FEvent> m_onMenuDelete;
    };
}
