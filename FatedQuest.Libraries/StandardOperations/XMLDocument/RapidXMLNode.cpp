#include "RapidXMLNode.h"

using namespace FatedQuestLibraries;

RapidXMLNode::RapidXMLNode()
{
    m_name = "";
}

const std::string RapidXMLNode::Name() const
{
    return m_name;
}

void RapidXMLNode::SetName(const std::string& name)
{
    m_name = name;
}
