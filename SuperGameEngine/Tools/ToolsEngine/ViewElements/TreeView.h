#pragma once
#include <memory>
#include "../../ImGuiIncludes.h"

namespace SuperGameEngine
{
    class SuperTexture;
    class ContentManager;
}

using namespace SuperGameEngine;

namespace SuperGameTools
{
    class TreeViewItem;

    /// <summary>
    /// Create and manages a tree view.
    /// </summary>//ImGuiTreeNodeFlags_CollapsingHeader
    class TreeView
    {
    public:
        TreeView(
            const std::shared_ptr<ContentManager>& contentManager,
            const std::shared_ptr<TreeViewItem>& treeViewItem);

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

        /// <summary>
        /// The depth at which indentations should occur.
        /// If set to 0 or below then indentations will occur from the start of the tree but not including the root.
        /// If set above 0, this depth will be the first level (and above) indentations will happen.
        /// </summary>
        /// <param name="depth">The depth at which indentations should occur. </param>
        void SetDepthToStartIndentation(int depth);

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
        /// The depth at which indentations should occur.
        /// If set to 0 or below then indentations will occur from the start of the tree.
        /// If set above 0, this depth will be the first level (and above) indentations will happen.
        /// </summary>
        int m_indentationDepth;

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        std::shared_ptr<ContentManager> m_contentManager;

        /// <summary>
        /// Texture for up arrow.
        /// </summary>
        std::shared_ptr<SuperTexture> m_upArrow;

        /// <summary>
        /// Texture for down arrow.
        /// </summary>
        std::shared_ptr<SuperTexture> m_downArrow;

        /// <summary>
        /// The size of the arrow.
        /// </summary>
        ImVec2 m_arrowSize;

        /// <summary>
        /// Renders a single item in the list.
        /// </summary>
        /// <param name="current">Current item to render. </param>
        /// <param name="depth">How deep we are in the tree. 0 is the root. </param>
        void RenderItem(const std::shared_ptr<TreeViewItem>& current, int depth) const;

        /// <summary>
        /// Render a single row.
        /// </summary>
        /// <param name="current">Current item. </param>
        /// <param name="depth">Depth in the tree. </param>
        void RenderRow(const std::shared_ptr<TreeViewItem>& current, int depth) const;

        void RenderSelectableArrow(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const;
        void RenderFullBackground(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const;
        void RenderSelectableRow(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const;
        void RenderArrowImage(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const;
        void RenderRowText(const std::shared_ptr<TreeViewItem>& current, ImVec2 originalPosition) const;
    };
}
