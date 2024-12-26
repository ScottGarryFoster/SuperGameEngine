#pragma once
#include "Engine.h"
#include <memory>
#include "ApplicationOperationState.h"
#include "../Engine/Graphics/Texture/SDLRenderer.h"

namespace SuperGameEngine
{
    class EngineFactory;

    /// <summary>
    /// The entry point for the engine and the top most level before main.
    /// </summary>
    class EngineEntry
    {
    public:
        /// <summary>
        /// The entry to the engine.
        /// </summary>
        /// <param name="engineFactory">
        /// Gives you the ability to create engines.
        /// </param>
        /// <param name="engineType">
        /// The type of the engine to create.
        /// The factory uses the type name to define which to create.
        /// </param>
        /// <returns>
        /// 0 means no errors occured when 
        /// attempting to start the application.
        /// </returns>
        virtual int RunApplication(const std::string& engineType);

    private:

        /// <summary>
        /// Creates the SDL Window loop.
        /// </summary>
        /// <param name="engineFactory">
        /// Gives you the ability to create engines.
        /// </param>
        /// <param name="engineType">
        /// The type of the engine to create.
        /// The factory uses the type name to define which to create.
        /// </param>
        /// <returns>
        /// How to handle exiting the game loop.
        /// </returns>
        ApplicationOperationState RunSDLWindow(const std::string& engineType);

        /// <summary>
        /// The renderer for the current window.
        /// This will flip flop and change with windows but is the
        /// active window.
        /// </summary>
        std::shared_ptr<SDLRenderer> m_renderer;

        /// <summary>
        /// If the engine is not destroyed between loops this is the engine.
        /// </summary>
        std::shared_ptr<Engine> m_engine;
    };
}