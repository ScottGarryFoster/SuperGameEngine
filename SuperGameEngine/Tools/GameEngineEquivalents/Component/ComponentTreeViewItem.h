#pragma once
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"

namespace SuperGameTools
{
    class Component;

    /// <summary>
    /// Renders a Component in the inspector
    /// </summary>
    class ComponentTreeViewItem : public TreeViewItem
    {
    public:
        ComponentTreeViewItem(const std::shared_ptr<ContentManager>& contentManager);

        /// <summary>
        /// Draw the tree view item.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// The component this item manages.
        /// </summary>
        /// <param name="component">The component this item manages. </param>
        virtual void SetComponent(const std::shared_ptr<Component>& component);

    private:
        /// <summary>
        /// The component this item manages.
        /// </summary>
        std::shared_ptr<Component> m_component;
    };
}
