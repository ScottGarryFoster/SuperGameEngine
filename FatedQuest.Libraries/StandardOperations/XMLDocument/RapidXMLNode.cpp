#include "RapidXMLNode.h"
#include "../AllReferences.h"

using namespace FatedQuestLibraries;

RapidXMLNode::RapidXMLNode()
{
    m_name = "";
    m_attributes = std::vector<std::shared_ptr<XMLAttribute>>();
    m_innerText = "";
}

const std::string RapidXMLNode::Name() const
{
    return m_name;
}

void RapidXMLNode::SetName(const std::string& name)
{
    m_name = name;
}

const std::vector<std::shared_ptr<XMLAttribute>> RapidXMLNode::Attributes() const
{
    return m_attributes;
}

const std::shared_ptr<XMLAttribute> FatedQuestLibraries::RapidXMLNode::Attribute(const std::string& criteria) const
{
    for (const std::shared_ptr<XMLAttribute>& attribute : m_attributes)
    {
        if (attribute->Name() == criteria)
        {
            return attribute;
        }
    }

    return std::shared_ptr<XMLAttribute>();
}

const std::shared_ptr<XMLAttribute> FatedQuestLibraries::RapidXMLNode::Attribute(const std::string& criteria, bool caseSensitive) const
{
    if (!caseSensitive)
    {
        return Attribute(criteria);
    }

    std::string lowerCriteria = StringHelpers::ToLower(criteria);
    for (const std::shared_ptr<XMLAttribute>& attribute : m_attributes)
    {
        if (StringHelpers::ToLower(attribute->Name()) == lowerCriteria)
        {
            return attribute;
        }
    }

    return std::shared_ptr<XMLAttribute>();
}

void RapidXMLNode::SetAttributes(std::vector<std::shared_ptr<XMLAttribute>> attributes)
{
    m_attributes = attributes;
}

const std::shared_ptr<XMLNode> RapidXMLNode::GetFirstChild() const
{
    return m_firstChild;
}

void RapidXMLNode::GiveFirstChild(std::shared_ptr<XMLNode> child)
{
    m_firstChild = child;
}

const std::shared_ptr<XMLNode> RapidXMLNode::GetLastChild() const
{
    return m_lastChild;
}

void RapidXMLNode::GiveLastChild(std::shared_ptr<XMLNode> child)
{
    m_lastChild = child;
}

const std::shared_ptr<XMLNode> RapidXMLNode::GetAdjacentNode() const
{
    return m_nextChild;
}

void RapidXMLNode::GiveAdjacentNode(std::shared_ptr<XMLNode> next)
{
    m_nextChild = next;
}

const std::string FatedQuestLibraries::RapidXMLNode::Inner() const
{
    return m_innerText;
}

void FatedQuestLibraries::RapidXMLNode::SetInner(const std::string& inner)
{
    m_innerText = inner;
}
