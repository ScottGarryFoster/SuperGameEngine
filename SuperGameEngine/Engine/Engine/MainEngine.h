#pragma once
#include "../EngineEntry/Engine.h"
#include <SDL.h>

namespace SuperGameEngine
{
    class EngineTextureManager;
    class GrandScene;
    class SuperGameTime;
    class TextureManager;
    class GrandScenePackage;
    class SuperGrandScenePackage;
    class DebugLogger;

    /// <summary>
    /// Main game engine.
    /// </summary>
    class MainEngine : public virtual Engine
    {
    public:

        MainEngine();
        ~MainEngine();

        /// <summary>
        /// Gives the engine a renderer.
        /// This can be called multiple times whilst the application is open
        /// as a user may decide to change certain settings which require
        /// re-creating the window.
        /// In this situation you should ensure everything using the renderer
        /// is recreated on this new renderer.
        /// </summary>
        /// <param name="renderer">The current window Renderer. </param>
        virtual void GiveRenderer(std::shared_ptr<SDLRendererReader> renderer) override;

        /// <summary>
        /// Gives the input manager.
        /// </summary>
        /// <param name="inputManager">User input. </param>
        virtual void GiveInput(const std::shared_ptr<SuperGameInput::SDLInputManager>& inputManager) override;

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        /// <returns>
        /// True means keep running the application.
        /// False will quit the application.
        /// </returns>
        virtual ApplicationOperationState Event(SDL_Event event) override;

        /// <summary>
        /// Update the application each frame.
        /// You must handle other things like Fixed Update.
        /// </summary>
        /// <param name="ticks">Ticks between this frame and the last. </param>
        /// <returns>
        /// True means keep running the application.
        /// False will quit the application.
        /// </returns>
        virtual ApplicationOperationState Update(Uint64 ticks) override;

        /// <summary>
        /// Draw to the screen.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Called as the window starts.
        /// </summary>
        virtual void WindowStart() override;

        /// <summary>
        /// Called when the window is torndown.
        /// </summary>
        virtual void WindowTeardown() override;

    private:

#ifdef _DEBUG
        /// <summary>
        /// Allows this to log issues to the console.
        /// </summary>
        std::shared_ptr<DebugLogger> m_logger;
#endif

        /// <summary>
        /// Handles and updates user input.
        /// </summary>
        std::shared_ptr<SuperGameInput::SDLInputManager> m_inputManager;

        /// <summary>
        /// Everything a grand scene needs to operate.
        /// </summary>
        //std::shared_ptr<GrandScenePackage> m_grandSceneLoadPackage;

        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// </summary>
        std::shared_ptr<EngineTextureManager> m_textureManager;

        /// <summary>
        /// Keeps track of time whilst the engine is running.
        /// </summary>
        std::shared_ptr<SuperGameTime> m_gameTime;

        /// <summary>
        /// Holds all scenes.
        /// </summary>
        std::shared_ptr<GrandScene> m_grandScene;

        /// <summary>
        /// The renderer to use for all textures.
        /// This needs to be at the level of SDL Renderers as this is one level down from the engine entry.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_renderer;

        /// <summary>
        /// Everything a grand scene needs to operate.
        /// </summary>
        std::shared_ptr<GrandScenePackage> m_grandSceneLoadPackage;

        /// <summary>
        /// True when the engine has loaded.
        /// </summary>
        bool m_haveLoaded;

        /// <summary>
        /// Sets up the engine for first time loading into a game.
        /// </summary>
        void Setup();

        /// <summary>
        /// Creates the Grand Scene Package.
        /// </summary>
        /// <returns>The created grand scene package. </returns>
        std::shared_ptr<GrandScenePackage> CreateGrandScenePackage();
    };
}