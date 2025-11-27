#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameTools
{
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
        virtual void SetupWindow(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles, const std::string& uniqueName) = 0;

        /// <summary>
        /// Start rendering window.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        /// <returns>True means is open. </returns>
        virtual bool RenderWindow(const char* name) = 0;

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
        virtual void HideWindow() = 0;

        /// <summary>
        /// Called when the window is shown or hidden.
        /// </summary>
        /// <returns>Called when the window is shown or hidden. </returns>
        /// <remarks>Uses these arguments <see cref="SuperGameTools::ToolsWindowShownArguments" /></remarks>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnWindowShownOrHidden() = 0;
    };
}

