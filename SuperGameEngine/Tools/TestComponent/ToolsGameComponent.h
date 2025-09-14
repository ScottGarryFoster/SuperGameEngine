#pragma once
#include "../../Engine/Structural/GameObject/ComponentFactory.h"
#include "../../Engine/Structural/Component/SuperGameComponent.h"

namespace SuperGameEngine
{
    class SuperTexture;

    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class ToolsGameComponent : public SuperGameComponent
    {
    public:
        ToolsGameComponent();
        virtual ~ToolsGameComponent() override;

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
            const std::weak_ptr <GameObject>& parent) override;

        /// <summary>
        /// The type to create to recreate this component.
        /// Override this on each component so that it always matches the type name for the class.
        /// </summary>
        /// <returns>The type to create to recreate this component. </returns>
        virtual std::string TypeName() const override;

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

    REGISTER_COMPONENT("ToolsComponent", ToolsGameComponent);
}