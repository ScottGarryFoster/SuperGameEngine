#pragma once
#include <SDL.h>
#include <memory>
#include "../../Engine/EngineEntry/Engine.h"
#include "../../Engine/Engine/Graphics/Texture/SDLRendererReader.h"
#include "../../Engine/Engine/Content/SuperTextureManager.h"
#include "../../Engine/Engine/Factory/EngineFactory.h"
#include "../../Engine/Engine/Basic/ExtremelyWeakWrapper.h"
#include "Engine/CrossEngineObjects/ToolsSharedSceneChangedEvents.h"

namespace SuperGameTools
{
    class ViewportEngineAndPanelCommunication;
    class CrossEngineObjects;
    class PanelManager;
}

namespace SuperGameEngine
{
    class SDLTextureChest;
    class SuperContentManager;
    class SuperGameTime;
    class SuperSceneLoadPackage;
    class GameObject;
}

using namespace SuperGameEngine;


namespace SuperGameTools
{
    class DockableContainer;
    class MainMenuBar;
    class EngineEntryCommunication;
    class UpdateableObject;
    class WindowPackage;

    /// <summary>
    /// An engine just for debugging. It is independent of  other engines.
    /// </summary>
    class ToolsEngine : public virtual Engine
    {
    public:
        ToolsEngine();
        virtual ~ToolsEngine();

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
        /// The data for the game.
        /// This is loaded in the engine entry as it contains information about the window state.
        /// </summary>
        /// <param name="gamePackage">The data for the game. </param>
        virtual void GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage) override;

        /// <summary>
        /// Give project properties which contains the information for how to treat the product.
        /// </summary>
        /// <param name="projectProperties">The foundational properties for setting up the project for the product. </param>
        virtual void GiveProjectProperties(const std::shared_ptr<ProjectProperties>& projectProperties) override;

        /// <summary>
        /// Allows you as the engine to communicate higher needs such as how to construct the viewport.
        /// </summary>
        /// <param name="engineControls">
        /// Allows you as the engine to communicate higher needs such as how to construct the viewport.
        /// </param>
        virtual void GiveControls(const std::shared_ptr<EngineControls>& engineControls) override;

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

        /// <summary>
        /// Called as the engine is created (ensure you have given the engine anything it requires).
        /// This will remake all the items in the engine.
        /// Do not call unless you would like the engine objects themselves torn down and therefore
        /// the state of the engine itself.
        /// </summary>
        virtual void EngineStart() override;

        /// <summary>
        /// Called as the engine is destroyed (ensure you have given the engine anything it requires).
        /// This will ensure that any setup is re-run on engine start.
        /// Do not call unless you would like the engine objects themselves torn down and therefore
        /// the state of the engine itself.
        /// </summary>
        virtual void EngineEnd() override;

        /// <summary>
        /// Gives the engine the texture the SDL Render is rendering to.
        /// This is used to display what the engine is doing.
        /// This texture is for the game viewport.
        /// </summary>
        /// <param name="sdlRenderTexture">The actual texture as a weak wrapper. </param>
        virtual void GiveSDLGameEngineTexture(const std::shared_ptr<SDLTextureChest>& sdlRenderTexture);

        /// <summary>
        /// Gives the engine the texture the SDL Render is rendering to.
        /// This is used to display what the engine is doing.
        /// This texture is for the tools viewport.
        /// </summary>
        /// <param name="sdlRenderTexture">The actual texture as a weak wrapper. </param>
        virtual void GiveSDLViewportTexture(const std::shared_ptr<SDLTextureChest>& sdlRenderTexture);

        /// <summary>
        /// Gives the ability for the tools engine to control
        /// the flow for the game engine.
        /// </summary>
        /// <param name="engineEntryCommunication">
        /// Communication with the Engine Entry.
        /// </param>
        virtual void GiveEnginePlayControls(const std::shared_ptr<EngineEntryCommunication>& engineEntryCommunication);

        /// <summary>
        /// Give this engine a reference to the objects shared by the main engine.
        /// </summary>
        /// <param name="crossEngineObjects">
        /// Holds links to objects which can be passed between engines within the tools.
        /// </param>
        void GiveCrossEngineObjects(const std::shared_ptr<CrossEngineObjects>& crossEngineObjects);

        /// <summary>
        /// Give object which allow the viewport engine and the panel which renders it to communicate information.
        /// </summary>
        /// <param name="engineAndPanelCommunication">New communication Object. </param>
        void GiveViewportEngineAndPanelCommunication(const std::shared_ptr<ViewportEngineAndPanelCommunication>& engineAndPanelCommunication);

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
        /// All the data for the game.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// Defines and communicates engine level changes you can manipulate.
        /// </summary>
        std::shared_ptr<EngineControls> m_engineControls;

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

        /// <summary>
        /// Gives the engine the texture the SDL Render is rendering to.
        /// This is used to display what the engine is doing.
        /// </summary>
        std::shared_ptr<SDLTextureChest> m_sdlGameViewportRenderTexture;

        /// <summary>
        /// Gives the engine the texture the SDL Render is rendering to.
        /// This is used to display what the tools engine (viewport) is doing.
        /// </summary>
        std::shared_ptr<SDLTextureChest> m_sdlToolsViewportRenderTexture;

        /// <summary>
        /// Everything a window needs to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// Holds content for the tools.
        /// </summary>
        std::shared_ptr<SuperContentManager> m_superContentManager;

        /// <summary>
        /// Communication with the Engine Entry.
        /// </summary>
        std::shared_ptr<EngineEntryCommunication> m_engineEntryCommunication;

        /// <summary>
        /// Enables docking in the entire window.
        /// Must be called first and you must call End() after all dockable windows.
        /// </summary>
        std::shared_ptr<DockableContainer> m_dockableContainer;

        /// <summary>
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        std::shared_ptr<SuperGameInput::SDLInputManager> m_inputManager;

        /// <summary>
        /// Manages panels, the visibility and layouts.
        /// </summary>
        std::shared_ptr<PanelManager> m_panelManager;

        /// <summary>
        /// Holds links to objects which can be passed between engines within the tools.
        /// </summary>
        std::shared_ptr<CrossEngineObjects> m_crossEngineObjects;

        /// <summary>
        /// Holds and links together events from the scene and inspector which contain core concepts
        /// such as 'oncomponentadded' which are in the main engine but affect behaviour in other engines.
        /// </summary>
        std::shared_ptr<ToolsSharedSceneChangedEvents> m_sharedSceneChangedEvents;

        /// <summary>
        /// Objects which allow the viewport engine and the panel which renders it to communicate information.
        /// </summary>
        std::shared_ptr<ViewportEngineAndPanelCommunication> m_viewportEngineAndPanelCommunication;

        /// <summary>
        /// Sets up the engine.
        /// </summary>
        void Setup();
    };

    REGISTER_ENGINE("ToolsEngine", ToolsEngine);
}