#include "ToolsComponent.h"

#include "SerializablePropertyLoader.h"
#include "../SerializableProperties/ToolsSerializableProperty.h"
#include "../../FatedQuestLibraries.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsComponent::ToolsComponent(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser)
{
    m_serializableParser = parser;
}

std::string ToolsComponent::GetType() const
{
    return m_type;
}

void ToolsComponent::SetType(const std::string& type)
{
    m_type = type;

    auto loader = std::make_shared<SerializablePropertyLoader>(m_serializableParser);
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

void ToolsComponent::Load(const std::shared_ptr<StoredDocumentNode>& node)
{
    std::string typeName = {};
    std::shared_ptr<StoredDocumentAttribute> typeAttribute = node->Attribute("Type", CaseSensitivity::IgnoreCase);
    if (typeAttribute)
    {
        typeName = typeAttribute->Value();
    }
    else
    {
        typeName = "Component";
    }

    // The component to the game object.
    SetType(typeName);

    for (std::shared_ptr<StoredDocumentNode> compChild = node->GetFirstChild(); compChild; compChild = compChild->GetAdjacentNode())
    {
        if (auto nameAttribute = compChild->Attribute("Name", CaseSensitivity::IgnoreCase))
        {
            for (const std::shared_ptr<ToolsSerializableProperty>& property : m_serializableToolsProperties)
            {
                if (nameAttribute->Value() == property->GetEngineProperty()->GetName())
                {
                    property->Load(compChild);
                }
            }
            
        }
    }
}

std::shared_ptr<ModifiableNode> ToolsComponent::Save() const
{
    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Component");

    // TODO: When we add Guids for Components this is where it would be saved.

    if (!GetType().empty())
    {
        auto guid = std::make_shared<ModifiableAttribute>("Type", GetType());
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(guid);
        node->SetAttributes(attributes);
    }

    auto children = std::vector<std::shared_ptr<ModifiableNode>>();
    for (const std::shared_ptr<ToolsSerializableProperty>& property : m_serializableToolsProperties)
    {
        if (auto propertyNode = property->Save())
        {
            children.emplace_back(propertyNode);
        }
    }
    node->SetAllChildrenNodes(children);

    return node;
}
