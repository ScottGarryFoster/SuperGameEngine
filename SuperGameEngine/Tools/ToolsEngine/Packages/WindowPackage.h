#pragma once
#include <memory>
#include <SDL_render.h>
#include "../../../Engine/Engine/Basic/ExtremelyWeakWrapper.h"

namespace SuperGameTools
{
    class ColoursAndStyles;
}

namespace FatedQuestLibraries
{
    class PackagePaths;
}

namespace SuperGameEngine
{
    class SerializableParser;
    class ContentManager;
    class SDLRendererReader;
}

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class FrameworkManager;
    class MenuView;
    class EngineEntryCommunication;
    class ColoursAndStyles;

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

        /// <summary>
        /// Gets a EngineEntryCommunication which allows communication with the Engine Entry.
        /// </summary>
        /// <returns>EngineEntryCommunication which allows communication with the Engine Entry. </returns>
        std::shared_ptr<EngineEntryCommunication> GetEngineEntryCommunication() const;

        /// <summary>
        /// Sets the EngineEntryCommunication.
        /// </summary>
        /// <param name="engineEntryCommunication">New EngineEntryCommunication. </param>
        void SetEngineEntryCommunication(const std::shared_ptr<EngineEntryCommunication>& engineEntryCommunication);

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        /// <returns>Helps to parse serializable objects. </returns>
        std::shared_ptr<SerializableParser> GetParser() const;

        /// <summary>
        /// Set parser.
        /// </summary>
        /// <param name="parser">New parser. </param>
        void SetParser(const std::shared_ptr<SerializableParser>& parser);

        /// <summary>
        /// Get the menu which is the menu going across the top of the
        /// application.
        /// </summary>
        /// <returns>The top menu. </returns>
        std::shared_ptr<MenuView> GetTopMenu() const;

        /// <summary>
        /// Set the new top menu.
        /// </summary>
        /// <param name="menuView">The top menu. </param>
        void SetTopMenu(const std::shared_ptr<MenuView>& menuView);

        /// <summary>
        /// Manages and holds the larger services for the entire tools engine.
        /// </summary>
        /// <returns>Manages and holds the larger services for the entire tools engine. </returns>
        std::shared_ptr<FrameworkManager> GetFrameworkManager() const;

        /// <summary>
        /// Manages and holds the larger services for the entire tools engine.
        /// </summary>
        /// <param name="frameworkManager">New framework manager. </param>
        void SetFrameworkManager(const std::shared_ptr<FrameworkManager>& frameworkManager);

        /// <summary>
        /// Helper class to grab paths.
        /// </summary>
        /// <returns>Helper class to grab paths. </returns>
        std::shared_ptr<PackagePaths> GetPackagePaths() const;

        /// <summary>
        /// Set package paths.
        /// </summary>
        /// <param name="packagePaths">Helper class to grab paths. </param>
        void SetPackagePaths(const std::shared_ptr<PackagePaths>& packagePaths);

        /// <summary>
        /// The colour palette used.
        /// </summary>
        /// <returns>The colour palette used. </returns>
        std::shared_ptr<ColoursAndStyles> GetColourPalette() const;

        /// <summary>
        /// Gives a colour palette.
        /// </summary>
        /// <param name="colourPalette">New palette. </param>
        void SetColourPalette(const std::shared_ptr<ColoursAndStyles>& colourPalette);
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

        /// <summary>
        /// Communication with the Engine Entry.
        /// </summary>
        std::shared_ptr<EngineEntryCommunication> m_engineEntryCommunication;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SerializableParser> m_serializableParser;

        /// <summary>
        /// The top menu bar.
        /// </summary>
        std::shared_ptr<MenuView> m_menuView;

        /// <summary>
        /// Manages and holds the larger services for the entire tools engine.
        /// </summary>
        std::shared_ptr<FrameworkManager> m_frameworkManager;

        /// <summary>
        /// Helper class to grab paths.
        /// </summary>
        std::shared_ptr<PackagePaths> m_packagePaths;

        /// <summary>
        /// The colour palette used.
        /// </summary>
        std::shared_ptr<ColoursAndStyles> m_colorPalette;
    };
}
