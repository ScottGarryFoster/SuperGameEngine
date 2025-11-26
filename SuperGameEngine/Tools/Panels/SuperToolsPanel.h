#pragma once
#include "ToolsPanel.h"
#include "ToolsEngine/ViewElements/Window/ToolsWindowElement.h"
#include "../../../FatedQuest.Libraries/StandardObjects/AllReferences.h"

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
    };
}
