#pragma once
#include "ToolsEngine/ViewElements/Window/WindowElement.h"
#include "UpdateableObject/UpdateableObject.h"

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
        /// If no settings have saved the panel state, how would you like this panel to
        /// begin. True means open.
        /// </summary>
        /// <returns>True means open, provided window settings or layouts do not say otherwise. </returns>
        virtual bool OpenState() const = 0;
    };
}
