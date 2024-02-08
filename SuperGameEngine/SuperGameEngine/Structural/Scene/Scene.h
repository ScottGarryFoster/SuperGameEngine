#pragma once
#include "../../Engine/Basic/GameTime.h"
#include "SceneLoadPackage.h"

namespace SuperGameEngine
{
    class GameObject;
    class Scene : public Object
    {
    public:
        Scene();
        ~Scene();

        /// <summary>
        /// Sets up the scene.
        /// </summary>
        /// <param name="sceneLoadPackage">Contains all the objects a GameObject needs to opperate. </param>
        void Setup(SceneLoadPackage* sceneLoadPackage);

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

        SceneLoadPackage* m_sceneLoadPackage;

        /// <summary>
        /// All game objects currently loaded.
        /// </summary>
        std::vector<GameObject*> m_gameObjects;

        SuperTexture* m_texture;
    };
}
