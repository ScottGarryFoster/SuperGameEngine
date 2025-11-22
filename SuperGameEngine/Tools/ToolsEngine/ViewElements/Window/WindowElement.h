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
        /// <summary>
        /// Sets up the window rendering code.
        /// </summary>
        /// <param name="colorsAndStyles">Helps to keep the colours and styles uniform.</param>
        virtual void SetupWindow(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles) = 0;

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
    };
}

