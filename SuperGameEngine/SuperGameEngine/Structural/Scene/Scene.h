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
        bool Update(GameTime gameTime);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();

    private:

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
        std::vector<GameObject*> m_gameObjects;

        SuperTexture* m_texture;
    };
}
