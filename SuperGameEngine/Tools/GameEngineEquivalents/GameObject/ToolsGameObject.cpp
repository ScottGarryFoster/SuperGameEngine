#include "ToolsGameObject.h"
#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"
#include "../Component/ToolsComponent.h"


using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsGameObject::ToolsGameObject(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser)
{
    m_serializableParser = parser;
    m_components = std::make_shared<std::vector<std::shared_ptr<Component>>>();

    // Put game object in these groups:
    m_selectionGroups.insert(SelectionGroup::Inspectable);

    m_onDirtyFlagChanged = std::make_shared<FEvent>();
    m_dirty = std::make_shared<bool>();
    *m_dirty = false;
}

std::shared_ptr<FEventSubscriptions> ToolsGameObject::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
}

std::shared_ptr<Guid> ToolsGameObject::GetGuid() const
{
    return m_guid;
}

std::unordered_set<SelectionGroup> ToolsGameObject::GetSelectionGroup() const
{
    return m_selectionGroups;
}

void ToolsGameObject::SetGuid(const std::shared_ptr<Guid>& guid)
{
    m_guid = guid;
}

std::shared_ptr<std::vector<std::shared_ptr<Component>>> ToolsGameObject::GetComponents() const
{
    return m_components;
}

void ToolsGameObject::RemoveComponent(const std::shared_ptr<Component>& component)
{
    std::erase_if(*m_components, [component](const std::shared_ptr<Component>& current)
    {
        return current->GetUniqueID()->ToString() == component->GetUniqueID()->ToString();
    });
}

void ToolsGameObject::Load(const std::shared_ptr<StoredDocumentNode>& node)
{
    bool createdGuid = false;
    if (std::shared_ptr<StoredDocumentAttribute> attribute = node->Attribute("Guid", CaseSensitivity::IgnoreCase))
    {
        if (!attribute->Value().empty())
        {
            SetGuid(GUIDHelpers::CreateFromString(attribute->Value()));
            createdGuid = true;
        }
    }

    if (!createdGuid)
    {
        SetGuid(GUIDHelpers::CreateGUID());
    }

    // Get rid of old information if any
    // Ensure we unsubscribe from old events.
    for (size_t i = 0; i < m_components->size(); ++i)
    {
        std::shared_ptr<Component> component = m_components->at(i);
        component->OnDirtyFlagChanged()->Unsubscribe(shared_from_this());
    }
    m_components->clear();

    for (std::shared_ptr<StoredDocumentNode> compChild = node->GetFirstChild(); compChild; compChild = compChild->GetAdjacentNode())
    {

        // The component to the game object.
        auto componentObject = std::make_shared<ToolsComponent>(m_serializableParser);
        componentObject->Load(compChild);
        componentObject->OnDirtyFlagChanged()->Subscribe(FEventObserver::shared_from_this());
        GetComponents()->emplace_back(componentObject);
    }

    UpdateDirtyFlag(false);
}

std::shared_ptr<ModifiableNode> ToolsGameObject::Save() const
{
    auto node = std::make_shared<ModifiableNode>();
    node->SetName("GameObject");
    if (m_guid)
    {
        auto guid = std::make_shared<ModifiableAttribute>("Guid", m_guid->ToString());
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(guid);
        node->SetAttributes(attributes);
    }

    auto children = std::vector<std::shared_ptr<ModifiableNode>>();
    for (size_t i = 0; i < m_components->size(); ++i)
    {
        std::shared_ptr<Component> component = m_components->at(i);
        children.emplace_back(component->Save());
    }
    node->SetAllChildrenNodes(children);

    UpdateDirtyFlag(false);
    return node;
}

std::shared_ptr<Component> ToolsGameObject::AddComponent(const std::string& type)
{
    auto component = std::make_shared<ToolsComponent>(m_serializableParser);
    component->SetType(type);
    component->Load();
    component->OnDirtyFlagChanged()->Subscribe(FEventObserver::shared_from_this());

    GetComponents()->emplace_back(component);
    UpdateDirtyFlag(true);

    return component;
}

void ToolsGameObject::Invoke(std::shared_ptr<FEventArguments> arguments)
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

void ToolsGameObject::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirty)
    {
        *m_dirty = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}