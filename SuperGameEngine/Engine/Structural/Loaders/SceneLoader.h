#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class StoredDocument;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class Scene;

    /// <summary>
    /// Loads a Scene from File.
    /// </summary>
    class SceneLoader
    {
    public:
        virtual ~SceneLoader() = default;

        /// <summary>
        /// Creates a new Scene from a stored document.
        /// </summary>
        /// <param name="storedDocument">Stored document object. Represents data originally loaded from file. </param>
        /// <returns>A new scene or null if could not create. </returns>
        virtual std::shared_ptr<Scene> Create(const std::shared_ptr<StoredDocument>& storedDocument) = 0;

        /// <summary>
        /// Save the scene to a store document format.
        /// </summary>
        /// <param name="scene">Scene to save. </param>
        /// <returns>Stored document or null if could not save. </returns>
        virtual std::shared_ptr<StoredDocument> Save(const std::shared_ptr<Scene>& scene) = 0;
    };
}

