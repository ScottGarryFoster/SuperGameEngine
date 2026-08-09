#include "ToolsTransformComponent.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "Engine/Graphics/ImGuiSuperTexture.h"
#include "GameEngineEquivalents/Component/ToolsComponent.h"
#include "GameEngineEquivalents/SerializableProperties/ToolsSerializableProperty.h"
#include "GameEngineEquivalents/SerializableProperties/Vector2FSerializableProperty.h"
#include "Structural/Serializable/SerializableProperty.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

bool ToolsTransformComponent::operator==(const ToolsTransformComponent& a) const
{
    if (!a.HasTransformComponent() && !HasTransformComponent())
    {
        return true;
    }

    if (a.HasTransformComponent() != HasTransformComponent())
    {
        return false;
    }

    return a.m_toolsComponent->GetObjectGuid()->ToString() == m_toolsComponent->GetObjectGuid()->ToString();
}

bool ToolsTransformComponent::operator==(const Component& a) const
{
    if (!HasTransformComponent())
    {
        return false;
    }

    return m_toolsComponent->GetObjectGuid()->ToString() == a.GetObjectGuid()->ToString();
}

bool ToolsTransformComponent::Initialize(const std::shared_ptr<Component>& component)
{
    m_toolsComponent = {};
    if (component->GetType() == "TransformComponent")
    {
        m_toolsComponent = component;
        UpdateProperties();
    }
    else
    {
        Log::Error("The correct type was not given.",
            "ToolsTransformComponent::ToolsTransformComponent(const std::shared_ptr<ToolsComponent>&");
    }

    return static_cast<bool>(m_toolsComponent);
    
}

void ToolsTransformComponent::Uninitialize()
{
    m_toolsComponent = {};
    m_positionTransform = {};
}

bool ToolsTransformComponent::HasTransformComponent() const
{
    return static_cast<bool>(m_toolsComponent);
}

void ToolsTransformComponent::SetPosition(float x, float y) const
{
    m_positionTransform->SetValue(x, y);
}

void ToolsTransformComponent::MovePositionBy(float x, float y) const
{
    m_positionTransform->ChangeValueBy(x, y);
}

void ToolsTransformComponent::UpdateProperties()
{
    for (const std::shared_ptr<ToolsSerializableProperty>& property : m_toolsComponent->GetToolsProperties())
    {
        if (auto engineProperty = property->GetEngineProperty())
        {
            if (engineProperty->GetType() == SerializableDataType::Vector2F && engineProperty->GetName() == "Position")
            {
                if (std::shared_ptr<Vector2FSerializableProperty> vector2F = 
                    std::dynamic_pointer_cast<Vector2FSerializableProperty>(property))
                {
                    m_positionTransform = vector2F;
                }
                else
                {
                    Log::Error("A property that looked like a position was not a vector2F. Could not register this.",
                        "ToolsTransformComponent::UpdateProperties()");
                }
            }
        }
    }
}
