#pragma once
#include <string>

#include "WindowManager.h"
#include "WindowPredefinedPosition.h"

namespace FatedQuestLibraries
{
    class FPoint;
}

namespace SuperGameEngine
{
    /// <summary>
    /// Provides the ability to create and manage the window the engine runs within.
    /// </summary>
    class EngineWindowManager : public virtual WindowManager
    {
    public:
        /// <summary>
        /// Creates new window.
        /// </summary>
        /// <param name="name">Title of the window. </param>
        /// <param name="position">Position to spawn the window. </param>
        /// <param name="size">Size of the window when spawned. </param>
        /// <return>True when could create window, false otherwise. Will log issues. </return>
        virtual bool CreateGameWindow(const std::string& name, WindowPredefinedPosition position, const FatedQuestLibraries::FPoint& size) = 0;

        /// <summary>
        /// Destroy the window created previously.
        /// Will do nothing if there is no window.
        /// </summary>
        virtual void DestroyWindow() = 0;
    };
}
