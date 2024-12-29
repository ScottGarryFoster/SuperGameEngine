#include "ModifiableNode.h"
#include "../StandardOperations/AllReferences.h"

using namespace FatedQuestLibraries;

ModifiableNode::ModifiableNode()
{
    m_name = {};
    m_attributes = {};
    m_firstChild = {};
    m_lastChild = {};
    m_adjacentNode = {};
    m_innerText = {};
}

const std::string ModifiableNode::Name() const
{
    return m_name;
}

void ModifiableNode::SetName(const std::string& newName)
{
    m_name = newName;
}

const std::vector<std::shared_ptr<StoredDocumentAttribute>> ModifiableNode::Attributes() const
{
    return m_attributes;
}

void ModifiableNode::SetAttributes(const std::vector<std::shared_ptr<StoredDocumentAttribute>>& newAttributes)
{
    m_attributes = newAttributes;
}

const std::shared_ptr<StoredDocumentAttribute> ModifiableNode::Attribute(const std::string& criteria) const
{
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributes)
    {
        if (attribute->Name() == criteria)
        {
            return attribute;
        }
    }

    return {};
}

const std::shared_ptr<StoredDocumentAttribute> ModifiableNode::Attribute(const std::string& criteria,
    bool caseSensitive) const
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

    return {};
}

const std::shared_ptr<StoredDocumentNode> ModifiableNode::GetFirstChild() const
{
    return m_firstChild;
}

void ModifiableNode::SetFirstChild(const std::shared_ptr<StoredDocumentNode>& firstChild)
{
    m_firstChild = firstChild;
}

const std::shared_ptr<StoredDocumentNode> ModifiableNode::GetLastChild() const
{
    return m_lastChild;
}

void ModifiableNode::SetLastChild(const std::shared_ptr<StoredDocumentNode>& lastChild)
{
    m_lastChild = lastChild;
}

const std::shared_ptr<StoredDocumentNode> ModifiableNode::GetAdjacentNode() const
{
    return m_adjacentNode;
}

void ModifiableNode::SetAdjacentNode(const std::shared_ptr<StoredDocumentNode>& adjacentNode)
{
    m_adjacentNode = adjacentNode;
}

const std::string ModifiableNode::Inner() const
{
    return m_innerText;
}

void ModifiableNode::SetInnerText(const std::string& innerText)
{
    m_innerText = innerText;
}
