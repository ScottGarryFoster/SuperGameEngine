#pragma once
#include <memory>
#include <vector>

#include "SelectionGroup.h"

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class Selectable;

    /// <summary>
    /// Manages selection across multiple windows.
    /// </summary>
    class SelectionManager
    {
    public:
        /// <summary>
        /// Event called when a selection has changed.
        /// </summary>
        /// <returns>Event called when a selection has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnSelectionChanged() const = 0;

        /// <summary>
        /// Event called when a selection has changed in the groups given.
        /// </summary>
        /// <param name="selectionGroup">Group to filter for. </param>
        /// <returns>Event called when a selection has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnSelectionChanged(SelectionGroup selectionGroup) const = 0;

        /// <summary>
        /// Add selectable to selection.
        /// </summary>
        /// <param name="selectable">New selection. </param>
        virtual void AddToSelection(const std::weak_ptr<Selectable>& selectable) = 0;

        /// <summary>
        /// Set the selection to this.
        /// Will only affect the groups this selection is in.
        /// </summary>
        /// <param name="selectable">New selection. </param>
        virtual void SetSelection(const std::weak_ptr<Selectable>& selectable) = 0;

        /// <summary>
        /// Remove selectable from selection.
        /// </summary>
        /// <param name="selectable">Removable selection. </param>
        virtual void RemoveFromSelection(const std::weak_ptr<Selectable>& selectable) = 0;

        /// <summary>
        /// Add selectable to selections.
        /// </summary>
        /// <param name="selectables">New selections. </param>
        virtual void AddToSelection(const std::vector<std::weak_ptr<Selectable>>& selectables) = 0;

        /// <summary>
        /// Set the selection to this.
        /// Will only affect the groups these selections are in.
        /// </summary>
        /// <param name="selectables">New selections. </param>
        virtual void SetSelection(const std::vector<std::weak_ptr<Selectable>>& selectables) = 0;

        /// <summary>
        /// Remove selectable from selections.
        /// </summary>
        /// <param name="selectables">Removable selections. </param>
        virtual void RemoveFromSelection(const std::vector<std::weak_ptr<Selectable>>& selectables) = 0;

        /// <summary>
        /// Get selection within given group.
        /// </summary>
        /// <param name="selectionGroup">Group to check. </param>
        /// <returns>All selectables in this group. </returns>
        virtual std::vector<std::weak_ptr<Selectable>> GetSelection(SelectionGroup selectionGroup) const = 0;

        /// <summary>
        /// Get selection within given groups.
        /// </summary>
        /// <param name="selectionGroup">Groups to check. </param>
        /// <returns>All selectables in the groups. </returns>
        virtual std::vector<std::weak_ptr<Selectable>> GetSelection(std::vector<SelectionGroup> selectionGroup) const = 0;
    };
}
