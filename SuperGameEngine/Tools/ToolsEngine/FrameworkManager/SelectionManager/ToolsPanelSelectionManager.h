#pragma once
#include "PanelSelectionManager.h"

namespace SuperGameTools
{
    /// <summary>
    /// Manages which panel is selected.
    /// </summary>
    class ToolsPanelSelectionManager : public PanelSelectionManager
    {
    public:

        ToolsPanelSelectionManager();

        /// <summary>
        /// Updates the selection to this panel.
        /// Used by the panels.
        /// </summary>
        /// <param name="newSelection">New selection. </param>
        virtual void UpdateNewSelection(PanelSelectionName newSelection) override;

        /// <summary>
        /// Gets the current panel selection.
        /// </summary>
        /// <returns>The current panel selection. </returns>
        virtual PanelSelectionName CurrentSelection() const override;

        /// <summary>
        /// Occurs when the selection has changed.
        /// Will use PanelSelectionChangedArguments.
        /// </summary>
        /// <returns>Occurs when the selection has changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnSelectionChanged() const override;

    private:

        /// <summary>
        /// Defines the name for each panel registered to the panel selection manager.
        /// </summary>
        PanelSelectionName m_panelSelectionName;

        /// <summary>
        /// Occurs when the selection has changed.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onSelectionChanged;
    };
}
