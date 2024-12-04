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
        /// <param name="sceneLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            std::shared_ptr<SceneLoadPackage> sceneLoadPackage,
            std::shared_ptr<GameObject> parent) override;

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
        virtual std::shared_ptr<GameObject> GetParent() const override;

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

    protected:

        /// <summary>
        /// Gets the scene load package.
        /// </summary>
        /// <returns>Everything a component needs to run. </returns>
        [[nodiscard]] std::shared_ptr<SceneLoadPackage> GetSceneLoadPackage() const;

    private:

        /// <summary>
        /// The parent game object.
        /// </summary>
        std::shared_ptr<GameObject> m_parent;

        /// <summary>
        /// Everything a component needs to run.
        /// </summary>
        std::shared_ptr<SceneLoadPackage> m_sceneLoadPackage;

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
    };
}
