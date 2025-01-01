#pragma once
#include <memory>

namespace SuperGameTools
{
    class TreeViewItem;

    /// <summary>
    /// Create and manages a tree view.
    /// </summary>//ImGuiTreeNodeFlags_CollapsingHeader
    class TreeView
    {
    public:
        TreeView(const std::shared_ptr<TreeViewItem>& treeViewItem);

        /// <summary>
        /// Draws the menu.
        /// </summary>
        void Draw() const;

        /// <summary>
        /// True means that the root element will be drawn within a frame.
        /// Useful for multiple trees which should be distinguished.
        /// </summary>
        /// <param name="shouldRootBeFrame">
        /// True means that the root element will be drawn within a frame.
        /// </param>
        void ShouldRootBeFrame(bool shouldRootBeFrame);

    private:
        /// <summary>
        /// The top element of the tree.
        /// </summary>
        std::shared_ptr<TreeViewItem> m_treeViewItemRoot;

        /// <summary>
        /// True means that the root element will be drawn within a frame.
        /// Useful for multiple trees which should be distinguished.
        /// </summary>
        bool m_shouldRootBeFramed;

        /// <summary>
        /// Renders a single item in the list.
        /// </summary>
        /// <param name="current">Current item to render. </param>
        /// <param name="isRoot">True means this is the first element in the tree. </param>
        void RenderItem(const std::shared_ptr<TreeViewItem>& current, bool isRoot) const;
    };
}
