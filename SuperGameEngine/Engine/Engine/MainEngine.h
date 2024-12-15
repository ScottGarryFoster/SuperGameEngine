#pragma once
#include "../EngineEntry/Engine.h"
#include <SDL.h>

namespace SuperGameEngine
{
    /// <summary>
    /// Main game engine.
    /// </summary>
    class MainEngine : public Engine
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
        virtual void GiveRenderer(std::shared_ptr<SDLRendererReader> renderer);

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        /// <returns>
        /// True means keep running the application.
        /// False will quit the application.
        /// </returns>
        virtual ApplicationOperationState Event(SDL_Event event);

        /// <summary>
        /// Update the application each frame.
        /// You must handle other things like Fixed Update.
        /// </summary>
        /// <param name="ticks">Ticks between this frame and the last. </param>
        /// <returns>
        /// True means keep running the application.
        /// False will quit the application.
        /// </returns>
        virtual ApplicationOperationState Update(Uint64 ticks);

        /// <summary>
        /// Draw to the screen.
        /// </summary>
        virtual void Draw();

        /// <summary>
        /// Called as the window starts.
        /// </summary>
        virtual void WindowStart();

        /// <summary>
        /// Called when the window is torndown.
        /// </summary>
        virtual void WindowTeardown();
};
}