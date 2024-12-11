#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class Guid;
}

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
        /// <summary>
        /// A unique identifier.
        /// </summary>
        virtual std::shared_ptr<FatedQuestLibraries::Guid> GetGuid() const = 0;

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
    };
};