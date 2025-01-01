#pragma once
#include <memory>

namespace SuperGameTools
{
    class TreeViewItem;

    /// <summary>
    /// Create and manages a tree view.
    /// </summary>
    class TreeView
    {
    public:
        TreeView(const std::shared_ptr<TreeViewItem>& treeViewItem);

        /// <summary>
        /// Draws the menu.
        /// </summary>
        void Draw() const;

    private:
        /// <summary>
        /// The top element of the tree.
        /// </summary>
        std::shared_ptr<TreeViewItem> m_treeViewItemRoot;

        /// <summary>
        /// Renders a single item in the list.
        /// </summary>
        /// <param name="current">Current item to render. </param>
        void RenderItem(const std::shared_ptr<TreeViewItem>& current) const;
    };
}
