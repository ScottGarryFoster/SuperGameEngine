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
    m_name = SanitizeAttribute(newName);
}

void ModifiableAttribute::SetValue(const std::string& newValue)
{
    m_value = SanitizeAttribute(newValue);
}

std::string ModifiableAttribute::SanitizeAttribute(const std::string& input) const
{
    if (input.size() < 3)
    {
        return input;
    }

    if (input.front() == '"' && input.back() == '"')
    {
        return input.substr(1, input.length() - 2);
    }

    return input;
}
