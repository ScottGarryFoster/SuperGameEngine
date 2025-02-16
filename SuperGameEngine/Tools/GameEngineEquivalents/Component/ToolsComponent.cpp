#include "ToolsComponent.h"

#include "SerializablePropertyLoader.h"
#include "../SerializableProperties/ToolsSerializableProperty.h"
#include "../../FatedQuestLibraries.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"


using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsComponent::ToolsComponent(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser)
{
    m_serializableParser = parser;
    m_onDirtyFlagChanged = std::make_shared<FEvent>();
    m_dirty = std::make_shared<bool>();
    *m_dirty = false;
    m_guid = GUIDHelpers::CreateGUID();
}

std::shared_ptr<Guid> ToolsComponent::GetUniqueID() const
{
    return m_guid;
}

std::shared_ptr<FEventSubscriptions> ToolsComponent::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
}

std::string ToolsComponent::GetType() const
{
    return m_type;
}

void ToolsComponent::SetType(const std::string& type)
{
    m_type = type;

    // Get rid of old information if any
    // Ensure we unsubscribe from old events.
    for (const std::shared_ptr<ToolsSerializableProperty>& serializableProperty : m_serializableToolsProperties)
    {
        serializableProperty->OnDirtyFlagChanged()->Unsubscribe(shared_from_this());
    }

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

    for (const std::shared_ptr<ToolsSerializableProperty>& serializableProperty : m_serializableToolsProperties)
    {
        serializableProperty->OnDirtyFlagChanged()->Subscribe(shared_from_this());
    }

    *m_dirty = false;
}

void ToolsComponent::Load()
{
    for (const std::shared_ptr<ToolsSerializableProperty>& serializableProperty : m_serializableToolsProperties)
    {
        serializableProperty->OnDirtyFlagChanged()->Subscribe(shared_from_this());
    }

    *m_dirty = false;
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

    *m_dirty = false;
    return node;
}

void ToolsComponent::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto dirtyArgs = std::dynamic_pointer_cast<DirtiedDataEventArguments>(arguments))
    {
        // Only respond if the children now have data to save
        // as if clean, this does not mean everything is clean,
        // only that something was saved.
        if (dirtyArgs->GetDirtyFlagState())
        {
            UpdateDirtyFlag(dirtyArgs->GetDirtyFlagState());
        }
    }
}

void ToolsComponent::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirty)
    {
        *m_dirty = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}