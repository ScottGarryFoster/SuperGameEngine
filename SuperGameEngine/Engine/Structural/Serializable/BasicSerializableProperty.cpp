#include "BasicSerializableProperty.h"

using namespace SuperGameEngine;

BasicSerializableProperty::BasicSerializableProperty()
{
    m_name = {};
    m_type = SerializableDataType::Unknown;
}

std::string BasicSerializableProperty::GetName() const
{
    return m_name;
}

void BasicSerializableProperty::SetName(const std::string& name)
{
    m_name = name;
}

SerializableDataType BasicSerializableProperty::GetType() const
{
    return m_type;
}

void BasicSerializableProperty::SetType(SerializableDataType type)
{
    m_type = type;
}
