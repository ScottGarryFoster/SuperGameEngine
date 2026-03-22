#pragma once
#include <SDL.h>

namespace SuperGameEngine
{
    /// <summary>
    /// Used to wrap an SDL_Texture.
    /// This version does the same as <cref="ExtremelyWeakWrapper" /> in that it will not
    /// interact with any of the destruction of the SDL framework and yet is the place of truth
    /// provided it is managed for a given texture.
    /// The advantage to this version is that you may forward declare this reference and avoid pulling
    /// in SDL which cannot be pulled into tests.
    /// </summary>
    class SDLTextureChest
    {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        SDLTextureChest();

        /// <summary>
        /// Construct with Texture from start.
        /// </summary>
        /// <param name="initialValue">Initial Texture. </param>
        SDLTextureChest(SDL_Texture* initialValue);

        /// <summary>
        /// The texture in this Class.
        /// This could be null pointer and could be destoryed outside
        /// of this class so do not store it and expect it to live forever.
        /// </summary>
        /// <returns>The texture in this Class. </returns>
        SDL_Texture* Get();

        /// <summary>
        /// Set a new value for this texture.
        /// </summary>
        /// <param name="newValue">The new value. </param>
        void Set(SDL_Texture* newValue);

    protected:

        /// <summary>
        /// The texture value.
        /// </summary>
        SDL_Texture* m_texture;
    };
}
