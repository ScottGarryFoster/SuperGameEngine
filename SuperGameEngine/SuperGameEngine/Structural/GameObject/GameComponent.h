#pragma once
#include "../../Engine/Basic/GameTime.h"
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    using namespace StandardCLibrary;

    class SceneLoadPackage;
    class GameObject;

    class GameComponent : public Object
    {
    public:
        GameComponent();
        virtual ~GameComponent();

        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent);

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(GameTime gameTime);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw();

        /// <summary>
        /// Gets the parent GameObject.
        /// </summary>
        /// <returns>The GameObject which owns us. </returns>
        GameObject* GetParent();

        void Test();
    private:

        /// <summary>
        /// Parent owning object.
        /// </summary>
        GameObject* m_parent;
    };
}