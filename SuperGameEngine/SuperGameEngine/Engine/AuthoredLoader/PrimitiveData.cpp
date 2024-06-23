#include "PrimitiveData.h"

using namespace SuperGameEngine;

PrimitiveData::PrimitiveData()
{
    m_name = std::string();
}

PrimitiveData::PrimitiveData(std::string& name, std::vector<std::shared_ptr<PrimitiveData>> children)
{
    m_name = name;

    for (const std::shared_ptr<PrimitiveData>& data : children)
    {
        m_children.push_back(std::static_pointer_cast<const PrimitiveData>(data));
    }
}

std::string PrimitiveData::GetName() const
{
    return m_name;
}

const std::vector<std::shared_ptr<const PrimitiveData>>& PrimitiveData::GetChildren() const
{
    return m_children;
}

const bool PrimitiveData::TryGetProperty(const std::string& propertyName, std::string& propertyValue) const
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

void PrimitiveData::SetProperty(const std::string& propertyName, const std::string& propertyValue)
{
    if (propertyName.empty())
    {
        return;
    }

    m_properties[propertyName] = propertyValue;
}
