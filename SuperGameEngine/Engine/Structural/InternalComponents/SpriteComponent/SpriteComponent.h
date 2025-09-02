#pragma once
#include "../../GameObject/ComponentFactory.h"
#include "../../Component/SuperGameComponent.h"
#include "../../../FatedQuestReferences.h"

namespace SuperGameEngine
{
    class TransformComponent;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{

    class TextureAsset;
    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class SpriteComponent : public SuperGameComponent
    {
    public:
        SpriteComponent();
        virtual ~SpriteComponent();

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
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) override;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() override;

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

        /// <summary>
        /// Updates the texture currently loaded.
        /// </summary>
        /// <param name="textureName">New texture loaded. </param>
        virtual void SetTexture(const std::string& textureName);

    private:

#pragma region Saved Properties

        /// <summary>
        /// The saved texture asset location.
        /// </summary>
        std::string m_propertyTextureAssetLocation;

        /// <summary>
        /// The name of the texture asset property saved.
        /// </summary>
        const char* m_propertyTextureAssetLocationName = "TextureAsset";

        /// <summary>
        /// The tile to render.
        /// </summary>
        int m_propertyTile;

        /// <summary>
        /// The name of tile to render.
        /// </summary>
        const char* m_propertyTileName = "Tile";

#pragma endregion

        /// <summary>
        /// Actual texture asset created on load or set.
        /// </summary>
        std::shared_ptr<TextureAsset> m_textureAsset;

        /// <summary>
        /// The transform for this game object.
        /// </summary>
        std::shared_ptr<TransformComponent> m_transform;
    };

    REGISTER_COMPONENT("SpriteComponent", SpriteComponent);
}

