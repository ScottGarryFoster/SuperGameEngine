#pragma once
#include <memory>

#include "EngineWindowManager.h"

namespace SuperGameEngine
{
    class SDLRenderer;

    /// <summary>
    /// Provides the ability to create and manage the window the engine runs within.
    /// </summary>
    class SDLEngineWindowManager : public virtual EngineWindowManager
    {
    public:

        /// <summary>
        /// A renderer should be created when the window is created.
        /// This is the renderer created when the window is created.
        /// </summary>
        /// <returns>A wrapper for SDL_Renderer to wrap the renderer from the SDL framework.</returns>
        virtual std::shared_ptr<SDLRenderer> GetDefaultRenderer() const = 0;
    };
}
