#include "ToolsComponent.h"

using namespace SuperGameTools;

std::string ToolsComponent::GetType() const
{
    return m_type;
}

void ToolsComponent::SetType(const std::string& type)
{
    m_type = type;
}
