#pragma once
#include <vector>

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
    };
}
