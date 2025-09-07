#pragma once
#include "../../GameObject/ComponentFactory.h"
#include "../../Component/SuperGameComponent.h"
#include "../../../FatedQuestReferences.h"

namespace SuperGameInput
{
    class InputHandler;
}

namespace SuperGameEngine
{
    class TransformComponent;
    class SpriteComponent;
}

namespace SuperGameEngine
{
    class TextureAsset;

    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class SimpleCharacterComponent : public SuperGameComponent
    {
    public:
        SimpleCharacterComponent();
        virtual ~SimpleCharacterComponent();

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
            const std::weak_ptr <GameObject>& parent) override;

        /// <summary>
        /// Setup run post load and is run everytime load is run.
        /// </summary>
        void PostLoadSetup();

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode) override;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::StoredDocumentNode> Save() override;

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

    private:

#pragma region Saved Properties

        /// <summary>
        /// The tile to set when moving north.
        /// </summary>
        KeyPairValue<const char*, int> m_propertyDirectionSpriteNorth;

        /// <summary>
        /// The tile to set when moving south.
        /// </summary>
        KeyPairValue<const char*, int> m_propertyDirectionSpriteSouth;

        /// <summary>
        /// The tile to set when moving east.
        /// </summary>
        KeyPairValue<const char*, int> m_propertyDirectionSpriteEast;

        /// <summary>
        /// The tile to set when moving west.
        /// </summary>
        KeyPairValue<const char*, int> m_propertyDirectionSpriteWest;

#pragma endregion

        /// <summary>
        /// True when this component is setup.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// The sprite upon this game object to represent the character.
        /// </summary>
        std::shared_ptr<SpriteComponent> m_spriteComponent;

        /// <summary>
        /// The transform for this game object.
        /// </summary>
        std::shared_ptr<TransformComponent> m_transform;

        /// <summary>
        /// A direct link to the input handler.
        /// </summary>
        std::shared_ptr<SuperGameInput::InputHandler> m_inputHandler;
    };

    REGISTER_COMPONENT("SimpleCharacterComponent", SimpleCharacterComponent);
}