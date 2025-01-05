#pragma once
#include <memory>
#include <string>

namespace SuperGameTools
{
    class ColoursAndStyles;

    /// <summary>
    /// Renders a window using ImGui.
    /// </summary>
    class WindowElement
    {
    public:
        WindowElement();

        /// <summary>
        /// Sets up the window rendering code.
        /// </summary>
        /// <param name="colorsAndStyles">Helps to keep the colours and styles uniform.</param>
        void Setup(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles);

        /// <summary>
        /// Start rendering window.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        /// <returns>True means is open. </returns>
        bool RenderWindow(const char* name);

        /// <summary>
        /// Call after all window code is complete.
        /// </summary>
        /// <param name="name">Name of the window.</param>
        void EndWindowRender(const char* name);

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
    };
}

