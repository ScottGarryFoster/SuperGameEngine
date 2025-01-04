#pragma once
#include <memory>

#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    class TreeViewItem;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Sent by all FEvents. Override this with custom event arguments.
    /// </summary>
    class TreeViewItemOnSelectedEventArguments : public FEventArguments
    {
    public:
        TreeViewItemOnSelectedEventArguments(const std::shared_ptr<TreeViewItem>& treeViewItem)
        {
            m_treeViewItem = treeViewItem;
        }
        virtual ~TreeViewItemOnSelectedEventArguments() override = default;

        /// <summary>
        /// The tree view item selected.
        /// </summary>
        /// <returns>The tree view item selected. </returns>
        std::shared_ptr<TreeViewItem> GetTreeViewItem()
        {
            return m_treeViewItem;
        }

        /// <summary>
        /// Set the tree view item selected.
        /// </summary>
        /// <param name="treeViewItem">The tree view item selected. </param>
        void SetTreeViewItem(const std::shared_ptr<TreeViewItem>& treeViewItem)
        {
            m_treeViewItem = treeViewItem;
        }

    private:
        /// <summary>
        /// Item selected.
        /// </summary>
        std::shared_ptr<TreeViewItem> m_treeViewItem;
    };
}
