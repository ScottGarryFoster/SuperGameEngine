#pragma once
#include "WindowElement.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameTools
{
    /// <summary>
    /// Renders a window using ImGui.
    /// </summary>
    class ToolsWindowElement : public virtual WindowElement
    {
    public:
        ToolsWindowElement();

        /// <summary>
        /// Sets up the window rendering code.
        /// </summary>
        /// <param name="colorsAndStyles">Helps to keep the colours and styles uniform.</param>
        void SetupWindow(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles) override;

        /// <summary>
        /// Start rendering window.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        /// <returns>True means is open. </returns>
        bool RenderWindow(const char* name) override;

        /// <summary>
        /// Call after all window code is complete.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        void EndWindowRender(const char* name) override;

        /// <summary>
        /// Shows the panel.
        /// </summary>
        void ShowWindow() override;

        /// <summary>
        /// Hides the panel.
        /// </summary>
        void HideWindow() override;

        /// <summary>
        /// Called when the window is shown or hidden.
        /// </summary>
        /// <returns>Called when the window is shown or hidden. </returns>
        /// <remarks>Uses these arguments <see cref="SuperGameTools::ToolsWindowShownArguments" /></remarks>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnWindowShownOrHidden() override;

    private:
        /// <summary>
        /// Helps to keep the colours and styles uniform.
        /// </summary>
        std::shared_ptr<ColoursAndStyles> m_coloursAndStyles;

        /// <summary>
        /// True when last state was open.
        /// </summary>
        bool m_currentOpenClosedState;

        /// <summary>
        /// True means is hovered. This is the tab not the window.
        /// </summary>
        bool m_tabIsHovered;

        /// <summary>
        /// True means the window is open.
        /// </summary>
        bool m_windowIsShown;

        /// <summary>
        /// Called when the window is shown or hidden.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onWindowShownOrHidden;

        /// <summary>
        /// The first window called.
        /// </summary>
        /// <remarks>
        /// This is used specifically for events.
        /// If we ever have this used for more than one window this should be an array.
        /// </remarks>
        std::string m_firstWindowCalled;
    };
}

