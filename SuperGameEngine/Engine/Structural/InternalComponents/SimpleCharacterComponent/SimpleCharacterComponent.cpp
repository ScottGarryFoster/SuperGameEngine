#include "SimpleCharacterComponent.h"

#include "../../../../Input/InputManagement/InputHandler.h"
#include "Structural/Serializable/PropertyByType/IntSerializableProperty.h"
#include "../TransformComponent/TransformComponent.h"
#include "../SpriteComponent/SpriteComponent.h"
#include "Structural/GameObject/GameObject.h"
#include "Structural/Serializable/SerializableParser.h"
#include "../../Packages/ComponentLoadPackage.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
using namespace SuperGameInput;

SimpleCharacterComponent::SimpleCharacterComponent()
{
    {
        m_propertyDirectionSpriteNorth.Key = "TileNorth";
        m_propertyDirectionSpriteNorth.Value = -1;
        auto property = std::make_shared<IntSerializableProperty>(m_propertyDirectionSpriteNorth.Value);
        property->SetName(m_propertyDirectionSpriteNorth.Key);
        m_serializableProperties.emplace_back(property);
    }

    {
        m_propertyDirectionSpriteSouth.Key = "TileSouth";
        m_propertyDirectionSpriteSouth.Value = -1;
        auto property = std::make_shared<IntSerializableProperty>(m_propertyDirectionSpriteSouth.Value);
        property->SetName(m_propertyDirectionSpriteSouth.Key);
        m_serializableProperties.emplace_back(property);
    }

    {
        m_propertyDirectionSpriteEast.Key = "TileEast";
        m_propertyDirectionSpriteEast.Value = -1;
        auto property = std::make_shared<IntSerializableProperty>(m_propertyDirectionSpriteEast.Value);
        property->SetName(m_propertyDirectionSpriteEast.Key);
        m_serializableProperties.emplace_back(property);
    }

    {
        m_propertyDirectionSpriteWest.Key = "TileWest";
        m_propertyDirectionSpriteWest.Value = -1;
        auto property = std::make_shared<IntSerializableProperty>(m_propertyDirectionSpriteWest.Value);
        property->SetName(m_propertyDirectionSpriteWest.Key);
        m_serializableProperties.emplace_back(property);
    }

    m_isSetup = false;
}

SimpleCharacterComponent::~SimpleCharacterComponent()
{
}

void SimpleCharacterComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::weak_ptr<GameObject>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);
    if (!IsSetup()) return;

    if (std::shared_ptr<GameObject> sharedParent = GetParent().lock())
    {
        const char* methodName = "SimpleCharacterComponent::Setup(const std::shared_ptr<ComponentLoadPackage>&,const std::weak_ptr<GameObject>&)";

        std::shared_ptr<GameComponent> transformAsGC = sharedParent->GetComponent("TransformComponent");
        if (transformAsGC)
        {
            if (std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(transformAsGC))
            {
                m_transform = transformComponent;
            }
            else
            {
                Log::Error("Transform component could not be cast. Cannot create a character without one.", methodName);
            }
        }
        else
        {
            Log::Error("No transform found on game object. Cannot create a character without one.", methodName);
        }

        std::shared_ptr<GameComponent> spriteAsGC = sharedParent->GetComponent("SpriteComponent");
        if (transformAsGC)
        {
            if (std::shared_ptr<SpriteComponent> spriteComponent = std::dynamic_pointer_cast<SpriteComponent>(transformAsGC))
            {
                m_spriteComponent = spriteComponent;
            }
            else
            {
                Log::Error("Sprite component could not be cast. Cannot create a character without one.", methodName);
            }
        }
        else
        {
            Log::Error("No sprite found on game object. Cannot create a character without one.", methodName);
        }
    }

    m_inputHandler = LoadPackage()->GetInput();

    m_isSetup = m_transform && m_spriteComponent && m_inputHandler;

    PostLoadSetup();
}

void SimpleCharacterComponent::PostLoadSetup()
{

}

void SimpleCharacterComponent::Load(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_propertyDirectionSpriteNorth.Value = LoadPackage()->GetParser()->ParseFromParent(m_propertyDirectionSpriteNorth.Key, -1, documentNode);
    m_propertyDirectionSpriteSouth.Value = LoadPackage()->GetParser()->ParseFromParent(m_propertyDirectionSpriteSouth.Key, -1, documentNode);
    m_propertyDirectionSpriteEast.Value = LoadPackage()->GetParser()->ParseFromParent(m_propertyDirectionSpriteEast.Key, -1, documentNode);
    m_propertyDirectionSpriteWest.Value = LoadPackage()->GetParser()->ParseFromParent(m_propertyDirectionSpriteWest.Key, -1, documentNode);

    PostLoadSetup();
}

std::shared_ptr<StoredDocumentNode> SimpleCharacterComponent::Save()
{
    std::shared_ptr<ModifiableNode> node = LoadPackage()->GetParser()->Serialize(std::make_shared<SimpleCharacterComponent>(*this));
    AddAnySuperGameComponentSaves(node);

    std::vector<std::shared_ptr<ModifiableNode>> children;
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_propertyDirectionSpriteNorth.Key, m_propertyDirectionSpriteNorth.Value, -1));
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_propertyDirectionSpriteSouth.Key, m_propertyDirectionSpriteSouth.Value, -1));
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_propertyDirectionSpriteEast.Key, m_propertyDirectionSpriteEast.Value, -1));
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_propertyDirectionSpriteWest.Key, m_propertyDirectionSpriteWest.Value, -1));

    node->SetAllChildrenNodes(children);

    return node;
}

std::string SimpleCharacterComponent::TypeName() const
{
    return "SimpleCharacterComponent";
}

void SimpleCharacterComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    if (m_isSetup) return;

    float x = m_inputHandler->AxisValueNormalised(UniversalControllerAxis::LeftStickX) * 50;
    float y = m_inputHandler->AxisValueNormalised(UniversalControllerAxis::LeftStickY) * 50;

    if (m_inputHandler->GetKeyDown(KeyCode::W))
    {
        y = -1;
    }
    else if (m_inputHandler->GetKeyDown(KeyCode::S))
    {
        y = 1;
    }

    if (m_inputHandler->GetKeyDown(KeyCode::A))
    {
        x = -1;
    }
    else if (m_inputHandler->GetKeyDown(KeyCode::D))
    {
        x = 1;
    }

    if (FloatingPointHelpers::AreEqual(x, 0) && FloatingPointHelpers::AreEqual(y, 0))
    {
        return;
    }

    auto movement = FVector2F(x, y).Normalize();
    if (FloatingPointHelpers::AreEqual(movement.GetX(), 0) && FloatingPointHelpers::AreEqual(movement.GetY(), 0))
    {
        return;
    }

    m_transform->MoveBy(movement);
}