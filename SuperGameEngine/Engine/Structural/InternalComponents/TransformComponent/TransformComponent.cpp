#include "TransformComponent.h"

#include "Structural/Packages/ComponentLoadPackage.h"
#include "Structural/Serializable/SerializableParser.h"
#include "../../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "Structural/Serializable/PropertyByType/Vector2FSerializableProperty.h"

using namespace SuperGameEngine;

TransformComponent::TransformComponent()
{
    m_position.SetXYValue(0, 0);

    {
        auto property = std::make_shared<Vector2FSerializableProperty>(m_position);
        property->SetName(m_positionName);
        m_serializableProperties.emplace_back(property);
    }
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::Setup(const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
                               const std::weak_ptr <GameObject>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);
    if (!IsSetup()) return;
}

void TransformComponent::Load(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_position = LoadPackage()->GetParser()->ParseFromParent(m_positionName, FVector2F(), documentNode);
}

std::shared_ptr<StoredDocumentNode> TransformComponent::Save()
{
    std::shared_ptr<ModifiableNode> node = LoadPackage()->GetParser()->Serialize(std::make_shared<TransformComponent>(*this));
    AddAnySuperGameComponentSaves(node);

    std::vector<std::shared_ptr<ModifiableNode>> children;
    children.emplace_back(LoadPackage()->GetParser()->Serialize(m_positionName, m_position, FVector2F()));

    node->SetFirstChild(children.at(0));

    return node;
}

std::string TransformComponent::TypeName() const
{
    return "TransformComponent";
}

const FVector2F& TransformComponent::Position() const
{
    return m_position;
}

FVector2F& TransformComponent::MoveBy(const FVector2F& other)
{
    m_position += other;
    return m_position;
}

FVector2F& TransformComponent::MoveBy(float scalar)
{
    m_position *= scalar;
    return m_position;
}

FVector2F& TransformComponent::ShrinkPositionBy(float scalar)
{
    m_position /= scalar;
    return m_position;
}
