#pragma once
#include <memory>

namespace SuperGameEngine
{
    class GameTime;
    class GrandScenePackage;
    class Scene;

    /// <summary>
    /// Holds everything in the entire game and manages the objects.
    /// </summary>
    class GrandScene
    {
    public:

        /// <summary>
        /// Sets up the Grand Scene.
        /// </summary>
        /// <param name="grandScenePackage">Everything a grand scene needs to run. </param>
        virtual void Setup(std::shared_ptr<GrandScenePackage> grandScenePackage) = 0;

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
        /// Draws the grand scene.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Creates new Scene and then adds it to the Grand Scene.
        /// </summary>
        /// <returns>New Scene added to the Grand Scene. </returns>
        virtual std::shared_ptr<Scene> CreateAndAddNewScene() = 0;

        /// <summary>
        /// Destroy the scene and all the game objects.
        /// </summary>
        virtual void Destroy() = 0;

        /// <summary>
        /// True means marked for destruction.
        /// </summary>
        /// <return>True means marked for destruction. </return>
        virtual bool IsDestroyed() const = 0;
    };
};