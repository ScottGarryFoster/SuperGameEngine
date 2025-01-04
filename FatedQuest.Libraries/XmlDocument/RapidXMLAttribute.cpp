#include "RapidXMLAttribute.h"

using namespace FatedQuestLibraries;

RapidXMLAttribute::RapidXMLAttribute()
{
    m_name = "";
    m_value = "";
}

RapidXMLAttribute::RapidXMLAttribute(const std::string& name, const std::string& value)
{
    m_name = name;
    m_value = value;
}

const std::string RapidXMLAttribute::Name() const
{
    return m_name;
}

void RapidXMLAttribute::SetName(const std::string& name)
{
    m_name = SanitizeAttribute(name);
}

const std::string RapidXMLAttribute::Value() const
{
    return m_value;
}

void RapidXMLAttribute::SetValue(const std::string& value)
{
    m_value = SanitizeAttribute(value);
}

std::string RapidXMLAttribute::SanitizeAttribute(const std::string& input) const
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
