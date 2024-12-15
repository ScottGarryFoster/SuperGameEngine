#pragma once
#include "../../GameObject/ComponentFactory.h"
#include "../../Component/SuperGameComponent.h"

namespace SuperGameEngine
{
    class SpriteComponent;

    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class TestComponent : public SuperGameComponent
    {
    public:
        TestComponent();
        virtual ~TestComponent();

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            std::shared_ptr<ComponentLoadPackage> componentLoadPackage,
            std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent) override;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

    private:

        std::shared_ptr<SpriteComponent> m_sprite;

        std::vector<std::shared_ptr<SpriteComponent>> m_bunchOfComponents;
    };

    REGISTER_COMPONENT("TestComponent", TestComponent);
}

