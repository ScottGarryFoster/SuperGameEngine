#pragma once
#include "Engine.h"
#include <memory>
#include "ApplicationOperationState.h"
#include "../Engine/Graphics/Texture/SDLRenderer.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameInput
{
    class SDLInputManager;
}

namespace SuperGameEngine
{
    class SDLEngineWindowManager;
    class EngineFactory;
    class ProjectProperties;

    /// <summary>
    /// The entry point for the engine and the top most level before main.
    /// </summary>
    class EngineEntry
    {
    public:
        virtual ~EngineEntry() = default;
        EngineEntry();

        /// <summary>
        /// The entry to the engine.
        /// </summary>
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
        /// <param name="engineType">
        /// The type of the engine to create.
        /// The factory uses the type name to define which to create.
        /// </param>
        /// <returns>
        /// How to handle exiting the game loop.
        /// </returns>
        ApplicationOperationState RunSDLWindow(const std::string& engineType);

        /// <summary>
        /// Holds and creates the window and renderer.
        /// </summary>
        std::shared_ptr<SDLEngineWindowManager> m_engineWindowManager;

        /// <summary>
        /// If the engine is not destroyed between loops this is the engine.
        /// </summary>
        std::shared_ptr<Engine> m_engine;

        /// <summary>
        /// Handles and updates user input.
        /// </summary>
        std::shared_ptr<SuperGameInput::SDLInputManager> m_inputManager;

        /// <summary>
        /// A directory of all paths for the game product.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// The foundational properties for setting up the project for the product.
        /// </summary>
        std::shared_ptr<ProjectProperties> m_projectProperties;

        /// <summary>
        /// Loads the project properties.
        /// </summary>
        /// <returns>True means could create. </returns>
        bool InitialiseProjectProperties();
    };
}
