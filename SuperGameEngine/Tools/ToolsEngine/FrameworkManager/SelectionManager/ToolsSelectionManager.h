#pragma once
#include <memory>
#include <vector>
#include "SelectionManager.h"

namespace SuperGameTools
{
    /// <summary>
    /// Manages selection across multiple windows.
    /// </summary>
    class ToolsSelectionManager : public SelectionManager
    {
    public:
        /// <summary>
        /// Add selectable to selection.
        /// </summary>
        /// <param name="selectable">New selection. </param>
        virtual void AddToSelection(const std::weak_ptr<Selectable>& selectable) override;

        /// <summary>
        /// Set the selection to this.
        /// Will only affect the groups this selection is in.
        /// </summary>
        /// <param name="selectable">New selection. </param>
        virtual void SetSelection(const std::weak_ptr<Selectable>& selectable) override;

        /// <summary>
        /// Remove selectable from selection.
        /// </summary>
        /// <param name="selectable">Removable selection. </param>
        virtual void RemoveFromSelection(const std::weak_ptr<Selectable>& selectable) override;

        /// <summary>
        /// Add selectable to selections.
        /// </summary>
        /// <param name="selectable">New selections. </param>
        virtual void AddToSelection(const std::vector<std::weak_ptr<Selectable>>& selectable) override;

        /// <summary>
        /// Set the selection to this.
        /// Will only affect the groups these selections are in.
        /// </summary>
        /// <param name="selectable">New selections. </param>
        virtual void SetSelection(const std::vector<std::weak_ptr<Selectable>>& selectable) override;

        /// <summary>
        /// Remove selectable from selections.
        /// </summary>
        /// <param name="selectable">Removable selections. </param>
        virtual void RemoveFromSelection(const std::vector<std::weak_ptr<Selectable>>& selectable) override;

        /// <summary>
        /// Get selection within given group.
        /// </summary>
        /// <param name="selectionGroup">Group to check. </param>
        /// <returns>All selectables in this group. </returns>
        virtual std::vector<std::weak_ptr<Selectable>> GetSelection(SelectionGroup selectionGroup) const override;

        /// <summary>
        /// Get selection within given groups.
        /// </summary>
        /// <param name="selectionGroup">Groups to check. </param>
        /// <returns>All selectables in the groups. </returns>
        virtual std::vector<std::weak_ptr<Selectable>> GetSelection(std::vector<SelectionGroup> selectionGroup) const override;
    };
}
