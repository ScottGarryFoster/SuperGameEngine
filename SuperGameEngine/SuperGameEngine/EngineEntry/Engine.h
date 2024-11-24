#pragma once
#include <SDL.h>

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
        virtual void GiveRenderer(SDL_Renderer* renderer) = 0;

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        /// <returns>
        /// True means keep running the application.
        /// False will quit the application.
        /// </returns>
        virtual bool Event(SDL_Event event) = 0;

        /// <summary>
        /// Update the application each frame.
        /// You must handle other things like Fixed Update.
        /// </summary>
        /// <param name="ticks">Ticks between this frame and the last. </param>
        /// <returns>
        /// True means keep running the application.
        /// False will quit the application.
        /// </returns>
        virtual bool Update(Uint64 ticks) = 0;

        /// <summary>
        /// Draw to the screen.
        /// </summary>
        virtual void Draw() = 0;
    };
}