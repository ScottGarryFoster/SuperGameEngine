#pragma once
#include <memory>

#include "FatedQuestLibraries.h"
#include "PanelSelectionName.h"

namespace SuperGameTools
{
    /// <summary>
    /// Manages which panel is selected.
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
