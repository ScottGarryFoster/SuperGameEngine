#pragma once
#include "CrossEngineObjects.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameTools
{
    /// <summary>
    /// Implements Cross Engine Objects for the Tools.
    /// </summary>
    class ToolsCrossEngineObjects : public CrossEngineObjects
    {
    public:

        ToolsCrossEngineObjects();

        /// <summary>
        /// Resets everything within this object.
        /// </summary>
        virtual void Reset() override;

        /// <summary>
        /// Get the current scene.
        /// </summary>
        /// <returns>Get the current scene. </returns>
        virtual std::shared_ptr<Scene> GetScene() const override;

        /// <summary>
        /// Set the scene given.
        /// </summary>
        /// <param name="scene">Set the new main scene. </param>
        virtual void SetScene(const std::shared_ptr<Scene>& scene) override;

        /// <summary>
        /// Called when a new scene is set as the current scene.
        /// Uses: OnSceneUpdatedEventArguments
        /// </summary>
        /// <returns>Called when a new scene is set as the current scene. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnNewScene() const override;

        /// <summary>
        /// Everything a Window might need to run.
        /// </summary>
        /// <returns>Everything a Window might need to run. </returns>
        virtual std::shared_ptr<WindowPackage> GetWindowPackage() const override;

        /// <summary>
        /// Gives a window package to the Tools sharing object.
        /// </summary>
        /// <param name="newValue">Gives a window package to the Tools sharing object. </param>
        virtual void SetWindowPackage(const std::shared_ptr<WindowPackage>& newValue) override;

        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// This should not be on using ImGui Rendering, it should use SDL rendering.
        /// </summary>
        /// <returns>Returns the texture manager. </returns>
        virtual const std::shared_ptr<SuperGameEngine::TextureManager> GetEngineTextureManager() const override;

        /// <summary>
        /// Gives the texture manager to be used by engines.
        /// This should not be on using ImGui Rendering, it should use SDL rendering.
        /// </summary>
        /// <returns>Returns the texture manager. </returns>
        virtual void SetEngineTextureManager(const std::shared_ptr<SuperGameEngine::TextureManager>& newValue) override;

    private:

        /// <summary>
        /// Current scene.
        /// </summary>
        std::shared_ptr<Scene> m_scene;

        /// <summary>
        /// Called when a new scene is set as the current scene.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onNewScene;

        /// <summary>
        /// Everything a Window might need to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// The texture manager used for engine based rendering.
        /// </summary>
        std::shared_ptr<SuperGameEngine::TextureManager> m_engineTextureManager;
    };
}

