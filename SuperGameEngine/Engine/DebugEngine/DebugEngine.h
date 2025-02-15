#pragma once
#include <SDL.h>
#include <memory>
#include "../EngineEntry/Engine.h"
#include "../Engine/Graphics/Texture/SDLRendererReader.h"
#include "../Engine/Content/SuperTextureManager.h"
#include "../Engine/Factory/EngineFactory.h"

namespace FatedQuestLibraries
{
    class CombinedGamePackage;
}

namespace SuperGameEngine
{
    class DebugLogger;
    class Scene;
    class GrandScene;
    class SuperGameTime;
    class SuperGrandScenePackage;
    class GameObject;
}

using namespace SuperGameEngine;


namespace SuperGameEngine
{

    /// <summary>
    /// An engine just for debugging. It is independent from other engines.
    /// </summary>
    class DebugEngine : public Engine
    {
    public:
        DebugEngine();
        virtual ~DebugEngine();

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
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opertunity.
        /// ApplicationOperationState::Close will close the game window at the next opertunity.
        /// </returns>
        virtual ApplicationOperationState Event(SDL_Event event) override;

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
        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// </summary>
        std::shared_ptr<SuperTextureManager> m_textureManager;

        /// <summary>
        /// Everything a grand scene needs to operate.
        /// </summary>
        std::shared_ptr<SuperGrandScenePackage> m_grandSceneLoadPackage;

        /// <summary>
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        std::shared_ptr<SuperGameInput::SDLInputManager> m_inputManager;

        std::shared_ptr<CombinedGamePackage> m_combinedGamePackage;

        std::shared_ptr<DebugLogger> m_logger;

        std::shared_ptr<SuperGameTime> m_gameTime;

        bool m_haveLoaded = false;
        bool m_haveRestartedWindow = false;

        std::shared_ptr<SuperTexture> m_superTexture;
        std::shared_ptr<SDLRendererReader> m_renderer;

        Uint64 t;
        Uint64 curr;

        std::shared_ptr<Scene> m_scene;
        std::shared_ptr<GameObject> m_go;
        bool m_haveSavedScene = false;

        /// <summary>
        /// Holds all scenes.
        /// </summary>
        std::shared_ptr<GrandScene> m_grandScene;

        /// <summary>
        /// Called once.
        /// </summary>
        void Setup();

        /// <summary>
        /// Creates the Grand Scene Package.
        /// </summary>
        void CreateGrandScenePackage();
    };

    REGISTER_ENGINE("DebugEngine", DebugEngine);
}