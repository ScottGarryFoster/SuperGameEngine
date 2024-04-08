#pragma once
#include "../../Engine/Basic/GameTime.h"
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    using namespace StandardCLibrary;

    class SceneLoadPackage;
    class GameObject;
    class Collision;

    /// <summary>
    /// A logical element attached to GameObjects.
    /// </summary>
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
        /// Frame-rate independent Update message for physics calculations.
        /// </summary>
        /// <param name="gameTime">Ticks since last frame. </param>
        virtual void FixedUpdate(GameTime gameTime);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw();

        /// <summary>
        /// Gets the parent GameObject.
        /// </summary>
        /// <returns>The GameObject which owns us. </returns>
        GameObject* GetParent();

        /// <summary>
        /// True means run a draw loop.
        /// By default this is to false as most Components will not need to draw anything
        /// and will instead use a Sprite Component to draw.
        /// </summary>
        /// <returns>Whether this Component does render. </returns>
        bool DoRender() const;

        /// <summary>
        /// Make this Component run Draw.
        /// Keep in mind that is just this Component not the whole GameObject!
        /// </summary>
        /// <param name="newValue">True means the draw loop will run.</param>
        void SetDoRender(bool newValue);

        /// <summary>
        /// A collision with something else has begin.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionBegin(Collision& collision);

        /// <summary>
        /// A collision is on going with another object.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionOccuring(Collision& collision);

        /// <summary>
        /// A collision has ended with something.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionEnd(Collision& collision);

    protected:
        /// <summary>
        /// Allows us to operate.
        /// </summary>
        SceneLoadPackage* m_loadPackage;

    private:

        /// <summary>
        /// Parent owning object.
        /// </summary>
        GameObject* m_parent;

        /// <summary>
        /// True means run a draw loop.
        /// By default this is to false as most Components will not need to draw anything
        /// and will instead use a Sprite Component to draw.
        /// </summary>
        bool m_doRender;
    };
}