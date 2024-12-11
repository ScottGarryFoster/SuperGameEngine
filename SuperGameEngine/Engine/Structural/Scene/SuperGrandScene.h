#pragma once
#include "GrandScene.h"
#include <memory>
#include <vector>

namespace SuperGameEngine
{
    class SceneLoadPackage;

    /// <summary>
    /// Holds everything in the entire game and manages the objects.
    /// </summary>
    class SuperGrandScene : public GrandScene
    {
    public:
        /// <summary>
        /// Sets up the Grand Scene.
        /// </summary>
        /// <param name="grandScenePackage">Everything a grand scene needs to run. </param>
        virtual void Setup(std::shared_ptr<GrandScenePackage> grandScenePackage) override;

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
        /// Draws the grand scene.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Creates new Scene and then adds it to the Grand Scene.
        /// </summary>
        /// <returns>New Scene added to the Grand Scene. </returns>
        virtual std::shared_ptr<Scene> CreateAndAddNewScene() override;

    private:
        /// <summary>
        /// Everything a grand scene needs to run.
        /// </summary>
        std::shared_ptr<GrandScenePackage> m_grandScenePackage;

        /// <summary>
        /// True means is setup.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// Everything a scene needs to load and exist.
        /// </summary>
        std::shared_ptr<SceneLoadPackage> m_sceneLoadPackage;

        /// <summary>
        /// All scenes in the order they will be rendered.
        /// </summary>
        std::vector<std::shared_ptr<Scene>> m_scenes;

        /// <summary>
        /// Scenes created but not yet in the render pool.
        /// This allows us to add to the scenes whilst updating.
        /// </summary>
        std::vector<std::shared_ptr<Scene>> m_pendingScenes;

        /// <summary>
        /// True means there are Pending scenes to update for
        /// the first time.
        /// </summary>
        bool m_isPendingScenes;

        /// <summary>
        /// Move pending update objects to the main updates.
        /// </summary>
        void MovePendingToMain();
    };
};