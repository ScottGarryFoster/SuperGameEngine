#pragma once
#include "SceneLoader.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Loads a Super Scene from File.
    /// </summary>
    class SuperSceneLoader : public SceneLoader
    {
    public:
        virtual ~SuperSceneLoader() override = default;

        /// <summary>
        /// Creates a new Scene from a stored document.
        /// </summary>
        /// <param name="storedDocument">Stored document object. Represents data originally loaded from file. </param>
        /// <returns>A new scene or null if could not create. </returns>
        virtual std::shared_ptr<Scene> Load(const std::shared_ptr<StoredDocument>& storedDocument) override;

        /// <summary>
        /// Save the scene to a store document format.
        /// </summary>
        /// <param name="scene">Scene to save. </param>
        /// <returns>Stored document or null if could not save. </returns>
        virtual std::shared_ptr<StoredDocument> Save(const std::shared_ptr<Scene>& scene) override;
    };
}
