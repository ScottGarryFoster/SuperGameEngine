#pragma once
#include <SDL.h>
#include <memory>
#include "../EngineEntry/Engine.h"
#include "../Engine/Graphics/Texture/SDLRendererReader.h"
#include "../Engine/Graphics/Texture/Texture.h"

using namespace SuperGameEngine;

namespace SuperEngineDebug
{
    /// <summary>
    /// An engine just for debuging. It is independant from other engines.
    /// </summary>
    class DebugEngine : public Engine
    {
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
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opertunity.
        /// ApplicationOperationState::Close will close the game window at the next opertunity.
        /// </returns>
        virtual ApplicationOperationState Event(SDL_Event event);

        /// <summary>
        /// Update the application each frame.
        /// You must handle other things like Fixed Update.
        /// </summary>
        /// <param name="ticks">Ticks between this frame and the last. </param>
        /// <returns>
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opertunity.
        /// ApplicationOperationState::Close will close the game window at the next opertunity.
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

    private:

        bool m_haveLoaded = false;
        bool m_haveRestartedWindow = false;

        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<SDLRendererReader> m_renderer;

        std::time_t originalTime;

        Uint64 t;
        Uint64 curr;
    };
}