#pragma once
#include "ToolsEngine/ViewElements/Window/WindowElement.h"
#include "UpdateableObject/UpdateableObject.h"

namespace SuperGameTools
{
    class PanelSelectionManager;
}

namespace SuperGameTools
{
    class ColoursAndStyles;
    
    /// <summary>
    /// Describes a Tools Panel.
    /// </summary>
    class ToolsPanel : public virtual UpdateableObject, public virtual WindowElement
    {
    public:

        /// <summary>
        /// The name of the window to draw.
        /// </summary>
        /// <returns>The name of the window to draw. </returns>
        virtual const char* GetPanelName() const = 0;

        /// <summary>
        /// The unique name of the panel. This must be unique to this panel.
        /// </summary>
        /// <returns>The unique name of the panel. This must be unique to this panel. </returns>
        virtual const char* GetPanelUniqueName() const = 0;

        /// <summary>
        /// If no settings have saved the panel state, how would you like this panel to
        /// begin. True means open.
        /// </summary>
        /// <returns>True means open, provided window settings or layouts do not say otherwise. </returns>
        virtual bool OnLoadOpenState() const = 0;

        /// <summary>
        /// Reset the panel for whatever that means, location, content etc.
        /// </summary>
        virtual void ResetPanel() = 0;

        /// <summary>
        /// Give the manager which manages the selection of panels amongst other panels.
        /// This will be used to communicate when this panel is selected to other panels.
        /// </summary>
        /// <param name="panelSelectionManager">The current selection manager. </param>
        virtual void GivePanelSelectionManager(const std::shared_ptr<PanelSelectionManager>& panelSelectionManager) = 0;
    };
}
