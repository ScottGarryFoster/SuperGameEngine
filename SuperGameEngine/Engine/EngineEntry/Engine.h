#pragma once
#include <SDL.h>
#include <memory>
#include "ApplicationOperationState.h"

namespace SuperGameInput
{
    class SDLInputManager;
    class InputHandler;
}

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameEngine
{
    class EngineControls;
    class SDLRendererReader;
    class ProjectProperties;

    /// <summary>
    /// An object capable of running applications such as games or tools.
    /// </summary>
    class Engine
    {
    public:
        /// <summary>
        /// Gives the engine a renderer.
        /// This can be called multiple times whilst the application is open
        /// as a user may decide to change certain settings which require
        /// re-creating the window.
        /// In this situation you should ensure everything using the renderer
        /// is recreated on this new renderer.
        /// </summary>
        /// <param name="renderer">The current window Renderer. </param>
        virtual void GiveRenderer(std::shared_ptr<SDLRendererReader> renderer) = 0;

        /// <summary>
        /// Gives the input manager.
        /// </summary>
        /// <param name="inputManager">User input. </param>
        virtual void GiveInput(const std::shared_ptr<SuperGameInput::SDLInputManager>& inputManager) = 0;

        /// <summary>
        /// The data for the game.
        /// This is loaded in the engine entry as it contains information about the window state.
        /// </summary>
        /// <param name="gamePackage">The data for the game. </param>
        virtual void GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage) = 0;

        /// <summary>
        /// Give project properties which contains the information for how to treat the product.
        /// </summary>
        /// <param name="projectProperties">The foundational properties for setting up the project for the product. </param>
        virtual void GiveProjectProperties(const std::shared_ptr<ProjectProperties>& projectProperties) = 0;

        /// <summary>
        /// Allows you as the engine to communicate higher needs such as how to construct the viewport.
        /// </summary>
        /// <param name="engineControls">
        /// Allows you as the engine to communicate higher needs such as how to construct the viewport.
        /// </param>
        virtual void GiveControls(const std::shared_ptr<EngineControls>& engineControls) = 0;

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        /// <returns>
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opportunity.
        /// ApplicationOperationState::Close will close the game window at the next opportunity.
        /// </returns>
        virtual ApplicationOperationState Event(SDL_Event event) = 0;

        /// <summary>
        /// Update the application each frame.
        /// You must handle other things like Fixed Update.
        /// </summary>
        /// <param name="ticks">Ticks between this frame and the last. </param>
        /// <returns>
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opportunity.
        /// ApplicationOperationState::Close will close the game window at the next opportunity.
        /// </returns>
        virtual ApplicationOperationState Update(Uint64 ticks) = 0;

        /// <summary>
        /// Draw to the screen.
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// Called as the window starts.
        /// </summary>
        virtual void WindowStart() = 0;

        /// <summary>
        /// Called when the window is torn down.
        /// </summary>
        virtual void WindowTeardown() = 0;

        /// <summary>
        /// Called as the engine is created (ensure you have given the engine anything it requires).
        /// This will remake all the items in the engine.
        /// Do not call unless you would like the engine objects themselves torn down and therefore
        /// the state of the engine itself.
        /// </summary>
        virtual void EngineStart() = 0;

        /// <summary>
        /// Called as the engine is destroyed (ensure you have given the engine anything it requires).
        /// This will ensure that any setup is re-run on engine start.
        /// Do not call unless you would like the engine objects themselves torn down and therefore
        /// the state of the engine itself.
        /// </summary>
        virtual void EngineEnd() = 0;
    };
}
