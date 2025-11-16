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
    class ProjectProperties;

    /// <summary>
    /// Provides the ability to create and manage the window the engine runs within.
    /// </summary>
    class EngineWindowManager : public virtual WindowManager
    {
    public:

        /// <summary>
        /// Setup the window manager.
        /// This can be run more than once and should be run if anything given fundamentally changes and
        /// it would be better to use the data from these.
        /// </summary>
        /// <param name="projectProperties">The foundational properties for setting up the project for the product. </param>
        virtual void Setup(const std::shared_ptr<ProjectProperties>& projectProperties) = 0;

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
