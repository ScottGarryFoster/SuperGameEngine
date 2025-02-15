#pragma once
#include <memory>
#include <vector>

#include "Scene.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class GameObjectLoadPackage;

    /// <summary>
    /// Holds and manages game objects
    /// </summary>
    class SuperScene : public Scene
    {
    public:
        SuperScene();
        virtual ~SuperScene() override;

        /// <summary>
        /// A unique identifier.
        /// </summary>
        virtual std::shared_ptr<Guid> GetGuid() const override;

        /// <summary>
        /// Sets Guid for this Scene.
        /// </summary>
        /// <param name="guid">Guid to update. </param>
        /// <remarks>
        /// Avoid calling this too often. It should be for setup.
        /// </remarks>
        void SetGuid(const std::shared_ptr<Guid>& guid);

        /// <summary>
        /// Sets up the Scene.
        /// </summary>
        /// <param name="grandScenePackage">Everything a grand scene needs to run. </param>
        virtual void Setup(std::shared_ptr<SceneLoadPackage> grandScenePackage) override;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const override;

        /// <summary>
        /// Updates the grand scene this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draws the scene.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Creates new GameObject and then adds it to the Scene.
        /// </summary>
        /// <returns>New GameObject added to the Scene. </returns>
        virtual std::shared_ptr<GameObject> CreateAndAddNewGameObject() override;

        /// <summary>
        /// Destroy the scene and all the game objects.
        /// </summary>
        virtual void Destroy() override;

        /// <summary>
        /// True means marked for destruction.
        /// </summary>
        /// <return>True means marked for destruction. </return>
        virtual bool IsDestroyed() const override;

        /// <summary>
        /// Destroys the scene immediately, calling all the code
        /// to destroy the scene and all it owns.
        /// </summary>
        virtual void DestroyImmediately() override;

        /// <summary>
        /// Any further cleanup after being destroyed by the parent
        /// should take place here. This is called after the parent
        /// has classed you as removed.
        /// </summary>
        virtual void OnDestroyed() override;

        /// <summary>
        /// Get children game object.
        /// </summary>
        /// <returns>All children of the scene. </returns>
        virtual std::vector<std::shared_ptr<GameObject>> GetChildren() const override;

        /// <summary>
        /// Gets the children on the Scene.
        /// This includes pending gameobjects which have not gone through an update.
        /// </summary>
        /// <returns>Gameobjects in scene. Only top level/direct are returned. </returns>
        virtual std::vector<std::shared_ptr<GameObject>> GetChildrenIncludingPending() const;

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) override;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() override;
    private:

        /// <summary>
        /// Unique identifier for the scene.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// True means is setup.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// True means scene is marked for destruction.
        /// </summary>
        bool m_isDestroyed;

        /// <summary>
        /// All game objects in the order of the scene which
        /// might be important for particular elements.
        /// </summary>
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;

        /// <summary>
        /// Game Objects which have not yet been updated.
        /// These are moved to the update loop each cycle.
        /// </summary>
        std::vector<std::shared_ptr<GameObject>> m_pendingGameObjects;

        /// <summary>
        /// True means there are Pending game objects.
        /// </summary>
        bool m_isPendingGameObjects;

        /// <summary>
        /// Everything the scene needs to run from the parent.
        /// </summary>
        std::shared_ptr<SceneLoadPackage> m_scenePackage;

        /// <summary>
        /// Everything a game object needs to run.
        /// </summary>
        std::shared_ptr<GameObjectLoadPackage> m_gameObjectPackage;

        /// <summary>
        /// Move pending update objects to the main updates.
        /// </summary>
        void MovePendingToMain();

        /// <summary>
        /// Destroy all the GameObjects marked for destruction.
        /// </summary>
        void DestroyAllDestroyedGameObjects();
    };
};