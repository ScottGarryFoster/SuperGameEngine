#pragma once
#include <SDL.h>
#include "SDLRendererState.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Wraps the SDL Renderer such that upon the death of the
    /// SDL Window this becomes invalid and the textures wait for a
    /// new texture.
    /// </summary>
    /// <remark>
    /// Would rather use Smartpointers here but I do not think I can with
    /// this pointer. This basically is doing the same thing.
    /// </remark>
    class SDLRendererReader
    {
    public:
        /// <summary>
        /// The SDL renderer from the window.
        /// Used to create textures and render to the screen.
        /// Might be nullptr.
        /// Might be destoryed! - So do not store it, use these methods instead.
        /// Used <see ref="SDLRendererState" /> to question this.
        /// </summary>
        /// <returns>The renderer to use when rendering to screen. </returns>
        SDL_Renderer* GetRenderer();

        /// <summary>
        /// Whether the renderer can be trusted or is active.
        /// </summary>
        /// <returns>Whether the renderer can be trusted or is active. </returns>
        SDLRendererState RendererState();

    protected:

        /// <summary>
        /// The SDL renderer from the window.
        /// Used to create textures and render to the screen.
        /// Might be nullptr.
        /// Might be destoryed!
        /// Used <see ref="SDLRendererState" /> to question this.
        /// </summary>
        SDL_Renderer* m_renderer;

        /// <summary>
        /// Whether the renderer can be trusted or is active.
        /// </summary>
        SDLRendererState m_rendererState;
    };
}