#pragma once
#include <vector>

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class GameObject;

    /// <summary>
    /// Holds game objects.
    /// </summary>
    class Scene
    {
    public:
        /// <summary>
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        /// <returns>Event called when this objects dirty flag has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnDirtyFlagChanged() const = 0;

        /// <summary>
        /// Saves Scene.
        /// </summary>
        /// <returns></returns>
        virtual bool Save() const = 0;

        /// <summary>
        /// Loads scene.
        /// </summary>
        virtual bool Load() = 0;

        /// <summary>
        /// Gets all game objects in scene.
        /// </summary>
        /// <returns>All game objects in scene. </returns>
        virtual std::vector<std::shared_ptr<GameObject>> GetGameObjects() const = 0;

        /// <summary>
        /// Deletes GameObject.
        /// </summary>
        /// <param name="gameObject">Game Object to erase. </param>
        virtual void RemoveGameObject(const std::shared_ptr<GameObject>& gameObject) = 0;

        /// <summary>
        /// True when there is unsaved data.
        /// </summary>
        /// <returns>True when there is unsaved data. </returns>
        virtual bool GetDirty() const = 0;

        /// <summary>
        /// Mark Scene Dirty.
        /// </summary>
        virtual void MarkDirty() = 0;

        /// <summary>
        /// Adds a game object to the scene.
        /// </summary>
        /// <param name="gameObject">New game object. </param>
        virtual void AddGameObject(const std::shared_ptr<GameObject>& gameObject) = 0;
    };
}
