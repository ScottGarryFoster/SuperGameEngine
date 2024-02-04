#pragma once
#include "../../Engine/Basic/GameTime.h"
#include "SceneLoadPackage.h"

namespace SuperGameEngine
{
    class Scene
    {
    public:
        Scene(SceneLoadPackage* sceneLoadPackage);
        ~Scene();

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

        bool m_intialised;

        SceneLoadPackage* m_sceneLoadPackage;

        SuperTexture* m_texture;
    };
}
