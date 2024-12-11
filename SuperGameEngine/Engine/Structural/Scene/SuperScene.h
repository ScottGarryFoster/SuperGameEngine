#pragma once
#include <memory>
#include <vector>

#include "Scene.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class SuperGameObjectLoadPackage;

    /// <summary>
    /// Holds and manages game objects
    /// </summary>
    class SuperScene : public Scene
    {
    public:
        SuperScene();
        virtual ~SuperScene();

        /// <summary>
        /// A unique identifier.
        /// </summary>
        virtual std::shared_ptr<Guid> GetGuid() const override;

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
        std::shared_ptr<SuperGameObjectLoadPackage> m_gameObjectPackage;

        /// <summary>
        /// Move pending update objects to the main updates.
        /// </summary>
        void MovePendingToMain();
    };
};