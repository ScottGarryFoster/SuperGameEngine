#pragma once
#include <memory>

#include "FatedQuestLibraries.h"
#include "PanelSelectionName.h"

namespace SuperGameTools
{
    /// <summary>
    /// Manages which panel is selected.
    /// Selected in this context means focused or active.
    /// </summary>
    class PanelSelectionManager
    {
    public:

        /// <summary>
        /// Updates the selection to this panel.
        /// Used by the panels.
        /// </summary>
        /// <param name="newSelection">New selection. </param>
        virtual void UpdateNewSelection(PanelSelectionName newSelection) = 0;

        /// <summary>
        /// Inform the selection manager that if this panel is selected,
        /// ensure it is now deselected.
        /// </summary>
        /// <param name="deselection">Panel to deselect</param>
        virtual void DeselectIfSelected(PanelSelectionName deselection) = 0;

        /// <summary>
        /// Gets the current panel selection.
        /// </summary>
        /// <returns>The current panel selection. </returns>
        virtual PanelSelectionName CurrentSelection() const = 0;

        /// <summary>
        /// Occurs when the selection has changed.
        /// Will use PanelSelectionChangedArguments.
        /// </summary>
        /// <returns>Occurs when the selection has changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnSelectionChanged() const = 0;
    };
}
