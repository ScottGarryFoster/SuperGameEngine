#pragma once
#include "Engine.h"
#include <memory>
#include "ApplicationOperationState.h"
#include "../Engine/Graphics/Texture/SDLRenderer.h"

namespace SuperGameEngine
{
    class ImGuiContainer;

    /// <summary>
    /// The entry point for the engine and the top most level before main.
    /// </summary>
    class EngineEntry
    {
    public:
        /// <summary>
        /// The entry to the engine.
        /// </summary>
        /// <param name="engine">Engine to run. </param>
        /// <returns>
        /// 0 means no errors occured when 
        /// attempting to start the application.
        /// </returns>
        int RunApplication(std::shared_ptr<Engine> engine);

    private:

        /// <summary>
        /// Creates the SDL Window loop.
        /// </summary>
        ApplicationOperationState RunSDLWindow(std::shared_ptr<Engine> engine);

        /// <summary>
        /// The renderer for the current window.
        /// This will flip flop and change with windows but is the
        /// active window.
        /// </summary>
        std::shared_ptr<SDLRenderer> m_renderer;

        /// <summary>
        /// Wraps setup for imgui.
        /// </summary>
        std::shared_ptr<ImGuiContainer> m_imgui;
    };
}