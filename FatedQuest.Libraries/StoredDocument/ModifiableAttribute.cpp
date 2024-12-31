#include "ModifiableAttribute.h"

using namespace FatedQuestLibraries;

ModifiableAttribute::ModifiableAttribute()
{
    m_name = {};
    m_value = {};
}

ModifiableAttribute::ModifiableAttribute(const std::string& name, const std::string& value)
{
    SetName(name);
    SetValue(value);
}

const std::string ModifiableAttribute::Name() const
{
    return m_name;
}

const std::string ModifiableAttribute::Value() const
{
    return m_value;
}

void ModifiableAttribute::SetName(const std::string& newName)
{
    m_name = newName;
}

void ModifiableAttribute::SetValue(const std::string& newValue)
{
    m_value = newValue;
}
