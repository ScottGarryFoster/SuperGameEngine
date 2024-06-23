#include "ParsedData.h"

using namespace SuperGameEngine;

ParsedData::ParsedData()
{
    m_name = std::string();
}

ParsedData::ParsedData(std::string& name, std::vector<std::shared_ptr<ParsedData>> children)
{
    m_name = name;

    for (const std::shared_ptr<ParsedData>& data : children)
    {
        m_children.push_back(std::static_pointer_cast<const ParsedData>(data));
    }
}

const std::string ParsedData::GetName() const
{
    return m_name;
}

const std::vector<std::shared_ptr<const ParsedData>>& ParsedData::GetChildren() const
{
    return m_children;
}

const bool ParsedData::TryGetProperty(const std::string& propertyName, std::string& propertyValue) const
{
    bool found = false;
    propertyValue = std::string();

    auto it = m_properties.find(propertyName);
    if (it != m_properties.end())
    {
        propertyValue = it->second;
        found = true;
    }

    return found;
}

void ParsedData::SetProperty(const std::string& propertyName, const std::string& propertyValue)
{
    if (propertyName.empty())
    {
        return;
    }

    m_properties[propertyName] = propertyValue;
}

const bool ParsedData::TryGetProperty(const std::string& propertyName, int& propertyValue) const
{
    bool found = false;
    propertyValue = int();

    auto it = m_intProperties.find(propertyName);
    if (it != m_intProperties.end())
    {
        propertyValue = it->second;
        found = true;
    }

    return found;
}

void ParsedData::SetProperty(const std::string& propertyName, const int& propertyValue)
{
    if (propertyName.empty())
    {
        return;
    }

    m_intProperties[propertyName] = propertyValue;
}
