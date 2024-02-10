#pragma once
#include <SDL.h>
#include "SceneLoadPackage.h"
#include "Scene.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Holds everything in the entire game.
    /// </summary>
    class GrandScene
    {
    public:
        GrandScene(SDL_Renderer* renderer);
        ~GrandScene();

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        bool Update(Uint64 tick);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();

    private:
        /// <summary>
        /// Contains all the objects a GameObject needs to opperate.
        /// Can be given to other GameObjets freely.
        /// </summary>
        SceneLoadPackage* m_sceneLoadPackage;

        /// <summary>
        /// All the Scenes loaded.
        /// </summary>
        std::vector<Scene*> m_scenes;
    };
}