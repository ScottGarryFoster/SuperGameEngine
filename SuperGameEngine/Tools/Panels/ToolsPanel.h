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
        virtual const char* GetPanelName() = 0;
    };
}
