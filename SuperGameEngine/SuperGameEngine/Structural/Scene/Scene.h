#pragma once
#include "../../Engine/Basic/GameTime.h"
#include "SceneLoadPackage.h"

namespace SuperGameEngine
{
    class GameObject;
    class SceneToGameObjectPackage;
    class Scene : public Object
    {
    public:
        Scene();
        ~Scene();

        /// <summary>
        /// A unique identifier.
        /// </summary>
        std::shared_ptr<Guid> GetGuid();

        /// <summary>
        /// Sets up the scene.
        /// </summary>
        /// <param name="sceneLoadPackage">Contains all the objects a GameObject needs to opperate. </param>
        /// <param name="sceneToGameObjectPackage">Contains gameObject specfic loading items.</param>
        void Setup(SceneLoadPackage* sceneLoadPackage, SceneToGameObjectPackage* sceneToGameObjectPackage);

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        bool Update(const GameTime gameTime);

        /// <summary>
        /// Update which occurs at a set timing.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        void FixedUpdate(const GameTime gameTime);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();

        /// <summary>
        /// Creates new Game Object in the scene.
        /// </summary>
        /// <returns>New Game Object in the Scene.</returns>
        std::shared_ptr<GameObject> CreateNewGameObject();

        /// <summary>
        /// Gets all Game Objects.
        /// </summary>
        /// <returns>All GameObjects in the Scene. </returns>
        std::vector<std::shared_ptr<GameObject>> GetAllGameObjects();

        /// <summary>
        /// Called when GameObject is destroyed.
        /// Should be used to ensure you do not have a link back to the
        /// GameObject as a SharedPointer.
        /// </summary>
        /// <param name="guid">Guid of the GameObject.</param>
        virtual void OnGameObjectDestroyed(const Guid& guid);

    private:
        /// <summary>
        /// Unique identifier.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// Has setup run successfully?
        /// </summary>
        bool m_loaded;

        /// <summary>
        /// Contains all the objects a GameObject needs to opperate.
        /// Can be given to other GameObjets freely.
        /// </summary>
        SceneLoadPackage* m_sceneLoadPackage;

        /// <summary>
        /// Objects for the GameObject to operate which GameComponents do not need
        /// to worry about. Things like Collision which the GameObject should help
        /// manage but the Components should feel like are 'managed' by the GameObject.
        /// </summary>
        SceneToGameObjectPackage* m_sceneToGameObjectPackage;

        /// <summary>
        /// All game objects currently loaded.
        /// </summary>
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    };
}
