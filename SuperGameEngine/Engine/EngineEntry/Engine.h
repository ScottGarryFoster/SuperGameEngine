#pragma once
#include <SDL.h>
#include <memory>
#include "../Engine/Graphics/Texture/SDLRendererReader.h"
#include "ApplicationOperationState.h"

namespace SuperGameInput
{
    class InputHandler;
}

namespace SuperGameEngine
{
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
        /// <param name="inputHandler">User input. </param>
        virtual void GiveInput(const std::shared_ptr<SuperGameInput::InputHandler>& inputHandler) = 0;

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
    };
}
