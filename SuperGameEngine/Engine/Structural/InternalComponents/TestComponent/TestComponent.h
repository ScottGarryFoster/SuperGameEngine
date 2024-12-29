#pragma once
#include "../../GameObject/ComponentFactory.h"
#include "../../Component/SuperGameComponent.h"

namespace SuperGameEngine
{
    class SuperTexture;
    class SpriteComponent;

    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class TestComponent : public SuperGameComponent
    {
    public:
        TestComponent();
        virtual ~TestComponent() override;

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
            const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent) override;

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

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) override;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() override;

    private:

        std::shared_ptr<SpriteComponent> m_sprite;

        std::vector<std::shared_ptr<SpriteComponent>> m_bunchOfComponents;

        /// <summary>
        /// A Texture which will move.
        /// </summary>
        std::shared_ptr<SuperTexture> m_testTexture;

        /// <summary>
        /// Testing Y position to give a little movement to the
        /// viewport.
        /// </summary>
        int m_yPosition;
    };

    REGISTER_COMPONENT("TestComponent", TestComponent);
}

