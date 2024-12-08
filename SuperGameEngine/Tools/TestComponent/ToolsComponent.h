#pragma once
#include "../../Engine/Structural/GameObject/ComponentFactory.h"
#include "../../Engine/Structural/Component/SuperGameComponent.h"

namespace SuperGameEngine
{
    class SuperTexture;

    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class ToolsComponent : public SuperGameComponent
    {
    public:
        ToolsComponent();
        virtual ~ToolsComponent();

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="sceneLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            std::shared_ptr<SceneLoadPackage> sceneLoadPackage,
            GameObject* parent) override;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draws the component.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

    private:

        std::shared_ptr<SuperTexture> m_superTexture;
    };

    REGISTER_COMPONENT("ToolsComponent", ToolsComponent);
}