#include "SpriteComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../Packages/ComponentLoadPackage.h"
#include "../../../Engine/Structural/Assets/Texture/SuperTextureAsset.h"
#include "../TransformComponent/TransformComponent.h"
#include "Structural/GameObject/GameObject.h"
#include "Structural/Serializable/PropertyByType/TextSerializableProperty.h"
#include "Structural/Serializable/SerializableParser.h"
#include "Structural/Serializable/PropertyByType/IntSerializableProperty.h"
#include "Structural/Serializable/PropertyByType/TextureAssetSerializableProperty.h"

using namespace SuperGameEngine;

SpriteComponent::SpriteComponent()
{
    {
        m_propertyTextureAssetLocation = "";
        auto property = std::make_shared<TextureAssetSerializableProperty>(m_propertyTextureAssetLocation);
        property->SetName(m_propertyTextureAssetLocationName);
        m_serializableProperties.emplace_back(property);
    }

    {
        m_propertyTile = 0;
        auto property = std::make_shared<IntSerializableProperty>(m_propertyTile);
        property->SetName(m_propertyTileName);
        m_serializableProperties.emplace_back(property);
    }
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::weak_ptr <GameObject>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);
    if (!IsSetup()) return;

    if (std::shared_ptr<GameObject> sharedParent = GetParent().lock())
    {
        std::shared_ptr<GameComponent> transformAsGC = sharedParent->GetComponent("TransformComponent");
        if (transformAsGC)
        {
            std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(transformAsGC);
            if (transformComponent)
            {
                m_transform = transformComponent;
            }
        }
    }

    PostLoadSetup();
}

void SpriteComponent::PostLoadSetup()
{
    if (!m_propertyTextureAssetLocation.empty())
    {
        SetTexture(m_propertyTextureAssetLocation);
    }
}

void SpriteComponent::Load(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_propertyTextureAssetLocation = LoadPackage()->GetParser()->ParseFromParent(m_propertyTextureAssetLocationName, "", documentNode);
    m_propertyTile = LoadPackage()->GetParser()->ParseFromParent(m_propertyTileName, 0, documentNode);

    PostLoadSetup();
}

std::shared_ptr<StoredDocumentNode> SpriteComponent::Save()
{
    std::shared_ptr<ModifiableNode> node = LoadPackage()->GetParser()->Serialize(std::make_shared<SpriteComponent>(*this));
    AddAnySuperGameComponentSaves(node);

    std::vector<std::shared_ptr<ModifiableNode>> children;
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_propertyTextureAssetLocationName, m_propertyTextureAssetLocation, ""));
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_propertyTileName, m_propertyTile, 0));

    node->SetAllChildrenNodes(children);

    return node;
}

std::string SpriteComponent::TypeName() const
{
    return "SpriteComponent";
}

void SpriteComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
    if (!IsSetup()) return;
}

void SpriteComponent::Draw() const
{
    SuperGameComponent::Draw();
    if (!IsSetup()) return;

    if (!m_textureAsset)
    {
        return;
    }

    if (!m_transform)
    {
        return;
    }

    m_textureAsset->Draw(m_propertyTile, m_transform->Position());
}

void SpriteComponent::SetTexture(const std::string& textureName)
{
    m_textureAsset = LoadPackage()->GetContentManager()->Texture()->GetTextureAsset(textureName);
    if (!m_textureAsset)
    {
        Log::Error("Could not create texture: "+ textureName, "SpriteComponent::SetTexture(const std::string&)");
    }

    // Ensure we render.
    bool haveTexture = m_textureAsset ? true : false;
    SetDoRender(haveTexture);
}

void SpriteComponent::SetTile(int tile)
{
    if (tile < 0)
    {
        Log::Error("Cannot set tile to draw to a negative number as this is not a valid tile",
            "SpriteComponent::SetTile(int)");
        return;
    }

    m_propertyTile = tile;
}
