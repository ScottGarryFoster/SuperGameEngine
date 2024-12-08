#pragma once
#include <SDL.h>
#include <memory>
#include "../../Engine/EngineEntry/Engine.h"
#include "../../Engine/Engine/Graphics/Texture/SDLRendererReader.h"
#include "../../Engine/Engine/Content/SuperTextureManager.h"
#include "../../Engine/Engine/Factory/EngineFactory.h"

namespace SuperGameEngine
{
    class SuperGameTime;
    class SuperSceneLoadPackage;
    class GameObject;
}

using namespace SuperGameEngine;


namespace SuperGameTools
{
    class UpdateableObject;

    /// <summary>
    /// An engine just for debugging. It is independent of  other engines.
    /// </summary>
    class ToolsEngine : public Engine
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
        virtual void GiveRenderer(std::shared_ptr<SDLRendererReader> renderer) override;

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        /// <returns>
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opportunity.
        /// ApplicationOperationState::Close will close the game window at the next opportunity.
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
        /// Everything a component needs to exist and operate.
        /// </summary>
        std::shared_ptr<SuperSceneLoadPackage> m_sceneLoadPackage;

        /// <summary>
        /// Everything we'll be running.
        /// </summary>
        std::vector<std::shared_ptr<UpdateableObject>> m_updatables;

        /// <summary>
        /// True means setup.
        /// </summary>
        bool m_haveSetup;

        /// <summary>
        /// Stores the renderer in a safe manner.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_renderer;
    };

    REGISTER_ENGINE("ToolsEngine", ToolsEngine);
}