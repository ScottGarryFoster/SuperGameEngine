#include "RapidXMLNode.h"
#include "FatedQuestLibraries.h"

using namespace FatedQuestLibraries;

RapidXMLNode::RapidXMLNode()
{
    m_name = "";
    m_attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
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

const std::vector<std::shared_ptr<StoredDocumentAttribute>> RapidXMLNode::Attributes() const
{
    return m_attributes;
}

const std::shared_ptr<StoredDocumentAttribute> RapidXMLNode::Attribute(const std::string& criteria) const
{
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributes)
    {
        if (attribute->Name() == criteria)
        {
            return attribute;
        }
    }

    return std::shared_ptr<StoredDocumentAttribute>();
}

const std::shared_ptr<StoredDocumentAttribute> RapidXMLNode::Attribute(const std::string& criteria, bool caseSensitive) const
{
    if (!caseSensitive)
    {
        return Attribute(criteria);
    }

    std::string lowerCriteria = StringHelpers::ToLower(criteria);
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributes)
    {
        if (StringHelpers::ToLower(attribute->Name()) == lowerCriteria)
        {
            return attribute;
        }
    }

    return std::shared_ptr<StoredDocumentAttribute>();
}

void RapidXMLNode::SetAttributes(std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes)
{
    m_attributes = attributes;
}

const std::shared_ptr<StoredDocumentNode> RapidXMLNode::GetFirstChild() const
{
    return m_firstChild;
}

void RapidXMLNode::GiveFirstChild(std::shared_ptr<StoredDocumentNode> child)
{
    m_firstChild = child;
}

const std::shared_ptr<StoredDocumentNode> RapidXMLNode::GetLastChild() const
{
    return m_lastChild;
}

void RapidXMLNode::GiveLastChild(std::shared_ptr<StoredDocumentNode> child)
{
    m_lastChild = child;
}

const std::shared_ptr<StoredDocumentNode> RapidXMLNode::GetAdjacentNode() const
{
    return m_nextChild;
}

void RapidXMLNode::GiveAdjacentNode(std::shared_ptr<StoredDocumentNode> next)
{
    m_nextChild = next;
}

const std::string RapidXMLNode::Inner() const
{
    return m_innerText;
}

void RapidXMLNode::SetInner(const std::string& inner)
{
    m_innerText = inner;
}

bool RapidXMLNode::AddAttribute(const std::shared_ptr<StoredDocumentAttribute>& attribute)
{
    if (!attribute)
    {
        Log::Warning("Attribute given was empty.", "RapidXMLNode::AddAttribute");
        return false;
    }

    std::string lowerCriteria = StringHelpers::ToLower(attribute->Name());
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributes)
    {
        if (StringHelpers::ToLower(attribute->Name()) == lowerCriteria)
        {
            return false;
        }
    }

    m_attributes.emplace_back(attribute);
    return true;
}

bool RapidXMLNode::RemoveAttribute(const std::string& attributeName)
{
    if (attributeName.empty())
    {
        Log::Warning("Attribute Name given was empty.", "RapidXMLNode::RemoveAttribute");
        return false;
    }

    std::shared_ptr<StoredDocumentAttribute> foundValue = {};
    std::string lowerCriteria = StringHelpers::ToLower(attributeName);
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributes)
    {
        if (StringHelpers::ToLower(attribute->Name()) == lowerCriteria)
        {
            foundValue = attribute;
            break;
        }
    }

    if (!foundValue)
    {
        return false;
    }

    VectorHelpers::RemoveValue(m_attributes, foundValue);
    return true;
}
