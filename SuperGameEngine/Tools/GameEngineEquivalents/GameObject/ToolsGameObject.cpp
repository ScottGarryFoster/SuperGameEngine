#include "ToolsGameObject.h"

using namespace SuperGameTools;

ToolsGameObject::ToolsGameObject()
{
    m_components = std::make_shared<std::vector<std::shared_ptr<Component>>>();
}

std::shared_ptr<Guid> ToolsGameObject::GetGuid() const
{
    return m_guid;
}

void ToolsGameObject::SetGuid(const std::shared_ptr<Guid>& guid)
{
    m_guid = guid;
}

std::shared_ptr<std::vector<std::shared_ptr<Component>>> ToolsGameObject::GetComponents() const
{
    return m_components;
}
