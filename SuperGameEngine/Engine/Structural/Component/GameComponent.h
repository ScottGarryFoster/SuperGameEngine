#pragma once
#include <memory>

#include "../../Engine/Basic/ExtremelyWeakWrapper.h"

namespace SuperGameEngine
{
    class GameObject;
    class SceneLoadPackage;
    class GameTime;

    class GameComponent
    {
    public:

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="sceneLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            std::shared_ptr<SceneLoadPackage> sceneLoadPackage,
            std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent) = 0;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const = 0;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Updates the component in fixed time.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void FixedUpdate(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Draws the component.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Gets the parent GameObject of this Component.
        /// This is given and stored as a raw pointer.
        /// For as long as the component exists this reference should exist.
        /// This reference however should never be stored or used outside a single method run
        /// by the game loop, Setup, Updates and Draw.
        /// </summary>
        /// <returns>The parent game object of this parent. </returns>
        virtual std::shared_ptr<ExtremelyWeakWrapper<GameObject>> GetParent() const = 0;

        /// <summary>
        /// True when this component should render.
        /// </summary>
        /// <returns>True when this component should render. </returns>
        virtual bool DoRender() const = 0;

        /// <summary>
        /// Updates whether this component should draw.
        /// </summary>
        /// <param name="newValue">True means this component should render. </param>
        virtual void SetDoRender(bool newValue) = 0;
    };
}
