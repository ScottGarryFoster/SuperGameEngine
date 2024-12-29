#pragma once
#include <memory>
#include <unordered_map>

#include "SceneStorageCache.h"

namespace FatedQuestLibraries
{
    class GamePackage;
    class StoredDocument;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class SceneLoader;

    class SuperSceneStorageCache : public SceneStorageCache
    {
    public:
        SuperSceneStorageCache();

        /// <summary>
        /// Sets up the cache.
        /// </summary>
        /// <param name="sceneLoader">Helps load up a scene from file. </param>
        /// <param name="gamePackage">Help to figure out where the files live. </param>
        virtual void Setup(
            const std::shared_ptr<SceneLoader>& sceneLoader, 
            const std::shared_ptr<GamePackage>& gamePackage);

        /// <summary>
        /// Get a scene from the cache as a new version of that scene.
        /// This will not reference anything else in the world except when using
        /// ObjectReference objects which can be resolved after.
        /// </summary>
        /// <param name="filePath">File path within the GamePackage. </param>
        /// <returns>A new version of the given scene or Null if it could not be created. </returns>
        virtual std::shared_ptr<Scene> GetScene(const std::string& filePath) override;

        /// <summary>
        /// Save an existing scene to file.
        /// </summary>
        /// <param name="scene">Scene to save. </param>
        /// <param name="filePath">File path to save to. If null or empty will use Scene for filename. </param>
        /// <returns>True means could save. </returns>
        virtual bool SaveScene(const std::shared_ptr<Scene>& scene, const std::string& filePath = {}) override;

    private:
        /// <summary>
        /// Helps to load scenes.
        /// </summary>
        std::shared_ptr<SceneLoader> m_sceneLoader;

        /// <summary>
        /// Gives us access to all the files the game cares about as these are 'on file'.
        /// </summary>
        std::shared_ptr<GamePackage> m_gamePackage;

        /// <summary>
        /// Actual cache for scenes.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<StoredDocument>> m_sceneFileCache;

        /// <summary>
        /// Load the scene directly from the file contents.
        /// </summary>
        /// <param name="filePath">File path.</param>
        /// <returns>A stored document representing the file or empty. </returns>
        std::shared_ptr<StoredDocument> LoadFromFileDirectly(const std::string& filePath) const;
    };

}

