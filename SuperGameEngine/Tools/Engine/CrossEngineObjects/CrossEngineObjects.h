#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameEngine
{
    class TextureManager;
}

namespace SuperGameTools
{
    class SharedSceneChangedEvents;
    class WindowPackage;
    class Scene;

    /// <summary>
    /// Holds links to objects which can be passed between engines within the tools.
    /// </summary>
    class CrossEngineObjects
    {
    public:

        /// <summary>
        /// Resets everything within this object.
        /// </summary>
        virtual void Reset() = 0;

        /// <summary>
        /// Called when a new scene is set as the current scene.
        /// </summary>
        /// <returns>Called when a new scene is set as the current scene. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnNewScene() const = 0;

        /// <summary>
        /// Everything a Window might need to run.
        /// </summary>
        /// <returns>Everything a Window might need to run. </returns>
        virtual std::shared_ptr<WindowPackage> GetWindowPackage() const = 0;

        /// <summary>
        /// Gives a window package to the Tools sharing object.
        /// </summary>
        /// <param name="newValue">Gives a window package to the Tools sharing object. </param>
        virtual void SetWindowPackage(const std::shared_ptr<WindowPackage>& newValue) = 0;

        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// This should not be on using ImGui Rendering, it should use SDL rendering.
        /// </summary>
        /// <returns>Returns the texture manager. </returns>
        virtual const std::shared_ptr<SuperGameEngine::TextureManager> GetEngineTextureManager() const = 0;

        /// <summary>
        /// Gives the texture manager to be used by engines.
        /// This should not be on using ImGui Rendering, it should use SDL rendering.
        /// </summary>
        /// <returns>Returns the texture manager. </returns>
        virtual void SetEngineTextureManager(const std::shared_ptr<SuperGameEngine::TextureManager>& newValue) = 0;

        /// <summary>
        /// Gets Shared Scene Changed Events.
        /// </summary>
        /// <returns>Gets Shared Scene Changed Events. </returns>
        virtual std::shared_ptr<SharedSceneChangedEvents> GetSharedSceneChangedEvents() const = 0;

        /// <summary>
        /// Gives this Shared Scene Changed Events.
        /// </summary>
        /// <param name="newValue">Gives this Shared Scene Changed Events. </param>
        virtual void SetSharedSceneChangedEvents(const std::shared_ptr<SharedSceneChangedEvents>& newValue) = 0;
    };
}
