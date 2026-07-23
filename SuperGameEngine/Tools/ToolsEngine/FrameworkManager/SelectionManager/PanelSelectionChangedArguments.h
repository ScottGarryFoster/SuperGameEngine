#pragma once
#include "PanelSelectionName.h"
#include "FatedQuestLibraries.h"

namespace SuperGameTools
{
    /// <summary>
    /// Occurs on Panel selection changed.
    /// </summary>
    class PanelSelectionChangedArguments : public FatedQuestLibraries::FEventArguments
    {
    public:

        PanelSelectionChangedArguments(PanelSelectionName newSelection)
        {
            m_panelSelectionName = newSelection;
        }

        /// <summary>
        /// The new selection after the selection is changed.
        /// </summary>
        /// <returns>The new selection after the selection is changed. </returns>
        PanelSelectionName GetSelectionName() const
        {
            return m_panelSelectionName;
        }

    private:

        /// <summary>
        /// Defines the name for each panel registered to the panel selection manager.
        /// </summary>
        PanelSelectionName m_panelSelectionName;
    };
}
