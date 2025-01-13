#include "ToolsComponent.h"

#include "SerializablePropertyLoader.h"
#include "../SerializableProperties/ToolsSerializableProperty.h"

using namespace SuperGameTools;

std::string ToolsComponent::GetType() const
{
    return m_type;
}

void ToolsComponent::SetType(const std::string& type)
{
    m_type = type;

    auto loader = std::make_shared<SerializablePropertyLoader>();
    m_serializableToolsProperties = loader->ToolsFromComponent(type);

    for (const std::shared_ptr<ToolsSerializableProperty>& property : m_serializableToolsProperties)
    {
        m_serializableProperties.emplace_back(property->GetEngineProperty());
    }
}

std::vector<std::shared_ptr<SerializableProperty>> ToolsComponent::GetProperties() const
{
    return m_serializableProperties;
}

std::vector<std::shared_ptr<ToolsSerializableProperty>> ToolsComponent::GetToolsProperties() const
{
    return m_serializableToolsProperties;
}
