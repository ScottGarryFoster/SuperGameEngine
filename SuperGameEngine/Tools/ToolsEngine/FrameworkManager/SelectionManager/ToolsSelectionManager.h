#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SelectionChangeType.h"
#include "SelectionManager.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameTools
{
    /// <summary>
    /// Manages selection across multiple windows.
    /// </summary>
    class ToolsSelectionManager : public SelectionManager
    {
    public:
        ToolsSelectionManager();

        /// <summary>
        /// Event called when a selection has changed.
        /// </summary>
        /// <returns>Event called when a selection has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnSelectionChanged() const override;

        /// <summary>
        /// Event called when a selection has changed in the groups given.
        /// </summary>
        /// <param name="selectionGroup">Group to filter for. </param>
        /// <returns>Event called when a selection has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnSelectionChanged(SelectionGroup selectionGroup) const override;

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
        /// <param name="selectables">New selections. </param>
        virtual void AddToSelection(const std::vector<std::weak_ptr<Selectable>>& selectables) override;

        /// <summary>
        /// Set the selection to this.
        /// Will only affect the groups these selections are in.
        /// </summary>
        /// <param name="selectables">New selections. </param>
        virtual void SetSelection(const std::vector<std::weak_ptr<Selectable>>& selectables) override;

        /// <summary>
        /// Remove selectable from selections.
        /// </summary>
        /// <param name="selectables">Removable selections. </param>
        virtual void RemoveFromSelection(const std::vector<std::weak_ptr<Selectable>>& selectables) override;

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

    private:
        /// <summary>
        /// All selectables by group.
        /// </summary>
        std::unordered_map<SelectionGroup, std::unordered_map<std::string, std::weak_ptr<Selectable>>> m_selectables;

        /// <summary>
        /// Events for OnSelectionChanged sorted by group.
        /// </summary>
        std::unordered_map<SelectionGroup, std::shared_ptr<FEvent>> m_onSelectionByGroup;

        /// <summary>
        /// Called for all groups.
        /// </summary>
        std::shared_ptr<FEvent> m_onSelectionForAllGroups;

        void CallOnSelection(SelectionChangeType change, const std::weak_ptr<Selectable>& selectable) const;

        void CallOnSelection(SelectionChangeType change, const std::vector<std::weak_ptr<Selectable>>& selectables) const;
    };
}
