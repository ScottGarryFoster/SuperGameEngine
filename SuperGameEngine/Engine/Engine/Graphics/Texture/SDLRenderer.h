#pragma once
#include <SDL.h>
#include "SDLRendererReader.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Wraps the SDL Renderer such that upon the death of the
    /// SDL Window this becomes invalid and the textures wait for a
    /// new texture.
    /// </summary>
    class SDLRenderer : public SDLRendererReader
    {
    public:
        SDLRenderer();

        /// <summary>
        /// Sets the renderer.
        /// This will handle updating states for textures throughout the
        /// engine.
        /// If creating a new renderer you will need to give this wrapper out.
        /// If removing a renderer you can set this to nullptr and this will not
        /// be used and then when you get the new renderer, create a new one and
        /// give that one out.
        /// </summary>
        /// <param name="newValue">New render value. </param>
        void SetRenderer(SDL_Renderer* newValue);
    };
}