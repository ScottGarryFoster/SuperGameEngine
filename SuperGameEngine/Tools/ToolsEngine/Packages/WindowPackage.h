#pragma once
#include <memory>
#include <SDL_render.h>
#include "../../../Engine/Engine/Basic/ExtremelyWeakWrapper.h"

namespace SuperGameEngine
{
    class ContentManager;
    class SDLRendererReader;
}

using namespace SuperGameEngine;

namespace SuperGameTools
{
    /// <summary>
    /// Everything a Window Package might need to run.
    /// </summary>
    class WindowPackage
    {
    public:

        /// <summary>
        /// Sets the render texture which the SDL window will render to.
        /// </summary>
        /// <param name="texture">The texture SDL is rendering to. </param>
        /// <remarks>Should be called by the engine entry. </remarks>
        void SetSDLRenderTexture(std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> texture);

        /// <summary>
        /// Gets the texture sdl will render to.
        /// </summary>
        /// <returns>The render texture sdl is rendering to. </returns>
        std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> GetSDLRenderTexture() const;

        /// <summary>
        /// Sets the renderer SDL is using for the whole window.
        /// </summary>
        /// <param name="sdlRendererReader">The renderer SDL is using for the whole window. </param>
        void SetRenderer(std::shared_ptr<SDLRendererReader> sdlRendererReader);

        /// <summary>
        /// The renderer SDL is using for the whole window.
        /// </summary>
        /// <returns>The renderer SDL is using for the whole window. </returns>
        std::shared_ptr<SDLRendererReader> GetRenderer() const;

        /// <summary>
        /// Gets a content manager which will be alive for the entire time the tools will be.
        /// </summary>
        /// <returns>The content manager. </returns>
        std::shared_ptr<ContentManager> GetContentManager() const;

        /// <summary>
        /// Sets the content Manager.
        /// </summary>
        /// <param name="contentManager">New content manager. </param>
        void SetContentManager(const std::shared_ptr<ContentManager>& contentManager);

    private:

        /// <summary>
        /// The render texture sdl is rendering to.
        /// </summary>
        std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> m_texture;

        /// <summary>
        /// Wraps the SDL Renderer such that upon the death of the
        /// SDL Window this becomes invalid and the textures wait for a
        /// new texture.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_renderer;

        /// <summary>
        /// The content manager for the game.
        /// </summary>
        std::shared_ptr<ContentManager> m_contentManager;
    };
}
