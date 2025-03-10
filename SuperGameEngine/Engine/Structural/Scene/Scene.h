#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class Guid;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class SceneLoadPackage;
    class GameObject;
    class GameTime;

    /// <summary>
    /// Holds and manages game objects
    /// </summary>
    class Scene
    {
    public:
        virtual ~Scene() = default;

        /// <summary>
        /// A unique identifier.
        /// </summary>
        virtual std::shared_ptr<Guid> GetGuid() const = 0;

        /// <summary>
        /// Sets up the Scene.
        /// </summary>
        /// <param name="grandScenePackage">Everything a grand scene needs to run. </param>
        virtual void Setup(std::shared_ptr<SceneLoadPackage> grandScenePackage) = 0;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const = 0;

        /// <summary>
        /// Updates the grand scene this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Draws the scene.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Creates new GameObject and then adds it to the Scene.
        /// </summary>
        /// <returns>New GameObject added to the Scene. </returns>
        virtual std::shared_ptr<GameObject> CreateAndAddNewGameObject() = 0;

        /// <summary>
        /// Destroy the scene and all the game objects.
        /// </summary>
        virtual void Destroy() = 0;

        /// <summary>
        /// True means marked for destruction.
        /// </summary>
        /// <return>True means marked for destruction. </return>
        virtual bool IsDestroyed() const = 0;

        /// <summary>
        /// Destroys the scene immediately, calling all the code
        /// to destroy the scene and all it owns.
        /// </summary>
        virtual void DestroyImmediately() = 0;

        /// <summary>
        /// Any further cleanup after being destroyed by the parent
        /// should take place here. This is called after the parent
        /// has classed you as removed.
        /// </summary>
        virtual void OnDestroyed() = 0;

        /// <summary>
        /// Get children game object.
        /// </summary>
        /// <returns>All children of the scene. </returns>
        virtual std::vector<std::shared_ptr<GameObject>> GetChildren() const = 0;

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) = 0;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() = 0;
    };
};