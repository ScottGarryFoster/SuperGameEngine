#pragma once
#include "../../Engine/Basic/GameTime.h"
#include "../../LibraryIncludes.h"
#include "ComponentFactory.h"

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
        /// Detirmines if the Setup has been called.
        /// This should be true pretty much always.
        /// If the game was just paused it could be false and therefore
        /// accessing this via the FixedUpdate loop could lead to errors.
        /// </summary>
        /// <returns>True means is setup. </returns>
        virtual bool IsSetup();

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(const GameTime gameTime);

        /// <summary>
        /// Frame-rate independent Update message for physics calculations.
        /// </summary>
        /// <param name="gameTime">Ticks since last frame. </param>
        virtual void FixedUpdate(const GameTime gameTime);

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

        /// <summary>
        /// Called when GameObject is destroyed.
        /// Should be used to ensure you do not have a link back to the
        /// GameObject as a SharedPointer.
        /// </summary>
        /// <param name="guid">Guid of the GameObject.</param>
        virtual void OnGameObjectDestroyed(const Guid& guid);

    protected:
        /// <summary>
        /// Allows us to operate.
        /// </summary>
        SceneLoadPackage* GetLoadPackage();

    private:

        /// <summary>
        /// Parent owning object.
        /// </summary>
        GameObject* m_parent;

        /// <summary>
        /// Allows us to operate.
        /// </summary>
        SceneLoadPackage* m_loadPackage;

        /// <summary>
        /// True means run a draw loop.
        /// By default this is to false as most Components will not need to draw anything
        /// and will instead use a Sprite Component to draw.
        /// </summary>
        bool m_doRender;

        /// <summary>
        /// True means setup has been called successfully in the base.
        /// </summary>
        bool m_isSetup;
    };
}