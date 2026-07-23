#pragma once
#include "ToolsPanel.h"
#include "ToolsEngine/ViewElements/Window/ToolsWindowElement.h"

namespace SuperGameTools
{
    class ColoursAndStyles;

    /// <summary>
    /// Describes a Tools Panel and implements it with ImGui Windows.
    /// </summary>
    class SuperToolsPanel : public virtual ToolsPanel, public ToolsWindowElement
    {
    public:
        SuperToolsPanel() : ToolsWindowElement() {}

        /// <summary>
        /// Reset the panel for whatever that means, location, content etc.
        /// </summary>
        virtual void ResetPanel() override {}

        /// <summary>
        /// Give the manager which manages the selection of panels amongst other panels.
        /// This will be used to communicate when this panel is selected to other panels.
        /// </summary>
        /// <param name="panelSelectionManager">The current selection manager. </param>
        virtual void GivePanelSelectionManager(const std::shared_ptr<PanelSelectionManager>& panelSelectionManager) override;

        /// <summary>
        /// Returns true if this panel is selected.
        /// </summary>
        /// <returns>Returns true if this panel is selected. </returns>
        virtual bool AreSelected() const override;

    protected:

        /// <summary>
        /// The manager which manages the selection of panels amongst other panels.
        /// This will be used to communicate when this panel is selected to other panels.
        /// </summary>
        std::shared_ptr<PanelSelectionManager> m_panelSelectionManager;

        /// <summary>
        /// The name of this panel.
        /// </summary>
        PanelSelectionName m_thisPanelsName;

        /// <summary>
        /// The current selected panel as far as we know.
        /// </summary>
        /// <remarks>
        /// This is cached as it is called every frame,
        /// to avoid us jumping around memory.
        /// </remarks>
        PanelSelectionName m_currentSelectedPanel;
    };
}
