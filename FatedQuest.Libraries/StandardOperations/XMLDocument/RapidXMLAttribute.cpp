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
    m_name = name;
}

const std::string RapidXMLAttribute::Value() const
{
    return m_value;
}

void RapidXMLAttribute::SetValue(const std::string& value)
{
    m_value = value;
}
