#pragma once
#include <memory>
#include <string>

namespace SuperGameEngine
{
    class Scene;

    /// <summary>
    /// Loads Scenes from File.
    /// </summary>
    class SceneStorageCache
    {
    public:

        /// <summary>
        /// Get a scene from the cache as a new version of that scene.
        /// This will not reference anything else in the world except when using
        /// ObjectReference objects which can be resolved after.
        /// </summary>
        /// <param name="filePath">File path within the GamePackage. </param>
        /// <returns>A new version of the given scene or Null if it could not be created. </returns>
        virtual std::shared_ptr<Scene> GetScene(const std::string& filePath) = 0;

        /// <summary>
        /// Save an existing scene to file.
        /// </summary>
        /// <param name="scene">Scene to save. </param>
        /// <param name="filePath">File path to save to. If null or empty will use Scene for filename. </param>
        /// <returns>True means could save. </returns>
        virtual bool SaveScene(const std::shared_ptr<Scene>& scene, const std::string& filePath = {}) = 0;
    };
}


