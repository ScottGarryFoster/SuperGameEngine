#pragma once
#include <string>

namespace QuestLauncher
{
    /// <summary>
    /// Creates and manages a window only used in the tray.
    /// </summary>
    class TrayWindow
    {
    public:
        virtual ~TrayWindow() = default;

        /// <summary>
        /// The title for the window.
        /// </summary>
        /// <returns>The title. </returns>
        virtual std::string GetTitle() const = 0;
    };
}


