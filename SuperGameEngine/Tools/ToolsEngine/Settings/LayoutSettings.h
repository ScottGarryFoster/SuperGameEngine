#pragma once

namespace SuperGameTools
{
    /// <summary>
    /// Settings about the main window.
    /// </summary>
    class LayoutSettings
    {
    public:
        virtual ~LayoutSettings() = default;

        /// <summary>
        /// The window width to use when creating the main window.
        /// </summary>
        /// <returns>The window width to use when creating the main window. </returns>
        virtual int WindowWidth() const = 0;

        /// <summary>
        /// The window height to use when creating the main window.
        /// </summary>
        /// <returns>The window height to use when creating the main window. </returns>
        virtual int WindowHeight() const = 0;

        /// <summary>
        /// The X position to start the window in.
        /// </summary>
        /// <returns>The X position to start the window in. </returns>
        virtual int WindowX() const = 0;

        /// <summary>
        /// The Y position to start the window in.
        /// </summary>
        /// <returns>The Y position to start the window in. </returns>
        virtual int WindowY() const = 0;
    };
}
