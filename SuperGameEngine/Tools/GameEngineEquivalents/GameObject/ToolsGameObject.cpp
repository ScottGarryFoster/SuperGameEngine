#include "ToolsGameObject.h"
#include "../../FatedQuestLibraries.h"
#include "../Component/ToolsComponent.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsGameObject::ToolsGameObject(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser)
{
    m_serializableParser = parser;
    m_components = std::make_shared<std::vector<std::shared_ptr<Component>>>();

    // Put game object in these groups:
    m_selectionGroups.insert(SelectionGroup::Inspectable);
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

    for (std::shared_ptr<StoredDocumentNode> compChild = node->GetFirstChild(); compChild; compChild = compChild->GetAdjacentNode())
    {

        // The component to the game object.
        auto componentObject = std::make_shared<ToolsComponent>(m_serializableParser);
        componentObject->Load(compChild);
        GetComponents()->emplace_back(componentObject);
    }
}

std::shared_ptr<ModifiableNode> ToolsGameObject::Save() const
{
    Log::Exception("Not created save.", "ToolsGameObject::Save()", "NotImplementedException");
    return {};
}
