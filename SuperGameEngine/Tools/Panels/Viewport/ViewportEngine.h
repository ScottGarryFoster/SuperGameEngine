#pragma once
#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "Engine/CrossEngineObjects/ViewportObjectDrawBundle.h"
#include "EngineEntry/Engine.h"

namespace SuperGameEngine
{
    class TextureAsset;
    class EngineTextureManager;
}

namespace SuperGameTools
{
    class CrossEngineObjects;

    class ViewportEngine : public virtual SuperGameEngine::Engine, public FatedQuestLibraries::FEventObserver
    {
    public:
        ViewportEngine();
        virtual ~ViewportEngine();

        /// <summary>
        /// Gives the engine a renderer.
        /// This can be called multiple times whilst the application is open
        /// as a user may decide to change certain settings which require
        /// re-creating the window.
        /// In this situation you should ensure everything using the renderer
        /// is recreated on this new renderer.
        /// </summary>
        /// <param name="renderer">The current window Renderer. </param>
        virtual void GiveRenderer(std::shared_ptr<SuperGameEngine::SDLRendererReader> renderer) override;

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
        virtual void GiveProjectProperties(const std::shared_ptr<SuperGameEngine::ProjectProperties>& projectProperties) override {}

        /// <summary>
        /// Allows you as the engine to communicate higher needs such as how to construct the viewport.
        /// </summary>
        /// <param name="engineControls">
        /// Allows you as the engine to communicate higher needs such as how to construct the viewport.
        /// </param>
        virtual void GiveControls(const std::shared_ptr<SuperGameEngine::EngineControls>& engineControls) override;

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        /// <returns>
        /// ApplicationOperationState::Running will keep the window running.
        /// ApplicationOperationState::Restart will restart the window at the next opportunity.
        /// ApplicationOperationState::Close will close the game window at the next opportunity.
        /// </returns>
        virtual SuperGameEngine::ApplicationOperationState Event(SDL_Event event) override;

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
        virtual SuperGameEngine::ApplicationOperationState Update(Uint64 ticks) override;

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
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

        /// <summary>
        /// Give this engine a reference to the objects shared by the main engine.
        /// </summary>
        /// <param name="crossEngineObjects">
        /// Holds links to objects which can be passed between engines within the tools.
        /// </param>
        void GiveCrossEngineObjects(const std::shared_ptr<CrossEngineObjects>& crossEngineObjects);

    private:

        /// <summary>
        /// The SDL Renderer we should output to.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SDLRendererReader> m_renderer;

        /// <summary>
        /// Handles and updates user input.
        /// </summary>
        std::shared_ptr<SuperGameInput::SDLInputManager> m_inputManager;

        /// <summary>
        /// All data for the game.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// </summary>
        std::shared_ptr<SuperGameEngine::EngineTextureManager> m_textureManager;

        /// <summary>
        /// A test texture for the first submit.
        /// </summary>
        std::shared_ptr<SuperGameEngine::TextureAsset> testTexture;

        /// <summary>
        /// Defines and communicates engine level changes.
        /// </summary>
        std::shared_ptr<SuperGameEngine::EngineControls> m_engineControls;

        /// <summary>
        /// Holds links to objects which can be passed between engines within the tools.
        /// </summary>
        std::shared_ptr<CrossEngineObjects> m_crossEngineObjects;

        /// <summary>
        /// Contains information to draw textures on the screen.
        /// </summary>
        ViewportObjectDrawBundle m_drawBundle;

        // TODO: We need texture manager in here, that is actually from the engine side not from the tools side because we are a
        // game engine here not a ImGui thing.
    };
}
