#pragma once
#include <memory>
#include <string>

#include "ToolsEngine/FrameworkManager/SelectionManager/PanelSelectionName.h"

namespace SuperGameTools
{
    class PanelSelectionManager;
}

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameTools
{
    struct SingleWindowLayoutSettings;
    class ColoursAndStyles;

    /// <summary>
    /// Renders a window using ImGui.
    /// Called a Panel in most places as opposed to a separate window.
    /// </summary>
    class WindowElement
    {
    public:
        /// <summary>
        /// Sets up the window rendering code.
        /// </summary>
        /// <param name="colorsAndStyles">Helps to keep the colours and styles uniform.</param>
        /// <param name="uniqueName">A unique name for this window. </param>
        /// <param name="layoutSettings">Defines the layout for a single window. </param>
        virtual void SetupWindow(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles, const std::string& uniqueName, const SingleWindowLayoutSettings& layoutSettings) = 0;

        /// <summary>
        /// Start rendering window.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        /// <returns>True means is open. </returns>
        virtual bool RenderWindow(const char* name) = 0;

        /// <summary>
        /// Handle selection of this panel.
        /// </summary>
        /// <param name="panelSelectionManager">Selection manager to inform of new selection. </param>
        /// <param name="panelSelectionName">The name of this panel if it is selected. </param>
        virtual void HandlePanelSelection(
            const std::shared_ptr<PanelSelectionManager>& panelSelectionManager,
            PanelSelectionName panelSelectionName
        ) const = 0 ;

        /// <summary>
        /// Call after all window code is complete.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        virtual void EndWindowRender(const char* name) = 0;

        /// <summary>
        /// Shows the panel.
        /// </summary>
        virtual void ShowWindow() = 0;

        /// <summary>
        /// Hides the panel.
        /// </summary>
        /// <return>True means window is hidden. </return>
        /// <remarks>Hiding is not hard , but you might not want a window to hide to allow windows to interject. </remark>
        virtual bool HideWindow() = 0;

        /// <summary>
        /// Called when the window is shown or hidden.
        /// </summary>
        /// <returns>Called when the window is shown or hidden. </returns>
        /// <remarks>Uses these arguments <see cref="SuperGameTools::ToolsWindowShownArguments" /></remarks>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnWindowShownOrHidden() = 0;

        /// <summary>
        /// Whether the window is currently open.
        /// </summary>
        /// <returns>True means the window is currently open. </returns>
        virtual bool OpenState() const = 0;

        /// <summary>
        /// Reset the window layout to how it began or last was set to in the layout.
        /// </summary>
        virtual void ResetWindowLayout() = 0;

        /// <summary>
        /// Update whether this window marks as 'unsaved'.
        /// This will add a little gui marker near the name of the panel to state there is unsaved work.
        /// </summary>
        /// <param name="newValue">True means document unsaved. </param>
        virtual void UpdateUnsavedState(bool newValue) = 0;

        /// <summary>
        /// Returns true if this panel is selected.
        /// </summary>
        /// <returns>Returns true if this panel is selected. </returns>
        virtual bool AreSelected() const = 0;

    protected:

        /// <summary>
        /// Deselects this panel.
        /// Used to ensure closed panels are not selected.
        /// </summary>
        virtual void Deselect() = 0;
    };
}

