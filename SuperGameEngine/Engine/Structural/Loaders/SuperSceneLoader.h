#pragma once
#include "SceneLoader.h"

namespace FatedQuestLibraries
{
    class ModifiableNode;
    class StoredDocumentNode;
}

namespace SuperGameEngine
{
    class SceneLoadPackage;
    class SuperScene;

    /// <summary>
    /// Loads a Super Scene from File.
    /// </summary>
    class SuperSceneLoader : public SceneLoader
    {
    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="sceneLoadPackage">Used for creating scenes. </param>
        SuperSceneLoader(const std::shared_ptr<SceneLoadPackage>& sceneLoadPackage);
        virtual ~SuperSceneLoader() override = default;

        /// <summary>
        /// Creates a new Scene from a stored document.
        /// </summary>
        /// <param name="storedDocument">Stored document object. Represents data originally loaded from file. </param>
        /// <returns>A new scene or null if could not create. </returns>
        virtual std::shared_ptr<Scene> Create(const std::shared_ptr<StoredDocument>& storedDocument) override;

        /// <summary>
        /// Save the scene to a store document format.
        /// </summary>
        /// <param name="scene">Scene to save. </param>
        /// <returns>Stored document or null if could not save. </returns>
        virtual std::shared_ptr<StoredDocument> Save(const std::shared_ptr<Scene>& scene) override;

    private:
        /// <summary>
        /// Everything a component needs to run.
        /// </summary>
        std::shared_ptr<SceneLoadPackage> m_sceneLoadPackage;

        void CreateSceneLevelAttributesAndNodes(const std::shared_ptr<StoredDocumentNode>& sceneNode, const std::shared_ptr<SuperScene>& scene) const;

        void SaveSceneLevelAttributesAndNodes(const std::shared_ptr<ModifiableNode>& sceneNode, const std::shared_ptr<Scene>& scene) const;
    };
}
