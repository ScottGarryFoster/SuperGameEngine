#pragma once
#include <memory>

#include "GameComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The implementation of a component.
    /// </summary>
    class SuperGameComponent : public GameComponent
    {
    public:
        SuperGameComponent();
        virtual ~SuperGameComponent();

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            std::shared_ptr<ComponentLoadPackage> componentLoadPackage,
            std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent) override;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const override;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Updates the component in fixed time.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void FixedUpdate(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draws the component.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Gets the parent GameObject of this Component.
        /// </summary>
        /// <returns>The parent game object of this parent. </returns>
        virtual std::shared_ptr<ExtremelyWeakWrapper<GameObject>> GetParent() const override;

        /// <summary>
        /// True when this component should render.
        /// </summary>
        /// <returns>True when this component should render. </returns>
        virtual bool DoRender() const override;

        /// <summary>
        /// Updates whether this component should draw.
        /// </summary>
        /// <param name="newValue">True means this component should render. </param>
        virtual void SetDoRender(bool newValue) override;

        /// <summary>
        /// Destroys the game object.
        /// </summary>
        virtual void Destroy() override;

        /// <summary>
        /// Is this GameObject marks for destruction.
        /// </summary>
        /// <returns>True means is marked for Destroyed. </returns>
        virtual bool IsDestroyed() const override;

        /// <summary>
        /// Destroys the component immediately, calling all the code
        /// to destroy the component and all it owns.
        /// </summary>
        virtual void DestroyImmediately() override;

        /// <summary>
        /// Any further cleanup after being destroyed by the parent
        /// should take place here. This is called after the parent
        /// has classed you as removed.
        /// </summary>
        virtual void OnDestroyed() override;
    protected:

        /// <summary>
        /// Gets the scene load package.
        /// </summary>
        /// <returns>Everything a component needs to run. </returns>
        [[nodiscard]] std::shared_ptr<ComponentLoadPackage> GetSceneLoadPackage() const;

    private:

        /// <summary>
        /// The parent game object.
        /// This is given and stored as a raw pointer.
        /// For as long as the component exists this reference should exist.
        /// This reference however should never be stored or used outside a single method run
        /// by the game loop, Setup, Updates and Draw.
        /// </summary>
        std::shared_ptr<ExtremelyWeakWrapper<GameObject>> m_parent;

        /// <summary>
        /// Everything a component needs to run.
        /// </summary>
        std::shared_ptr<ComponentLoadPackage> m_loadPackage;

        /// <summary>
        /// True means run a draw loop.
        /// By default, this is set to false as most Components will not need to draw anything
        /// and will instead use a Sprite Component to draw.
        /// </summary>
        bool m_doRender;

        /// <summary>
        /// True means setup has been called successfully in the base.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// True means marked for destruction.
        /// </summary>
        bool m_isDestroyed;
    };
}
