#include "PrimitiveData.h"

using namespace SuperGameEngine;

PrimitiveData::PrimitiveData()
{
    m_name = std::string();
}

PrimitiveData::PrimitiveData(std::string& name, std::vector<std::shared_ptr<PrimitiveData>> children)
{
    m_name = name;
    m_children = children;

}

std::string SuperGameEngine::PrimitiveData::GetName() const
{
    return m_name;
}

const std::vector<std::shared_ptr<PrimitiveData>>& PrimitiveData::GetChildren()
{
    return m_children;
}