#include "ModifiableNode.h"

#include "ModifiableAttribute.h"
#include "../Logger/Logger/Log.h"
#include "../StandardOperations/AllReferences.h"

using namespace FatedQuestLibraries;

ModifiableNode::ModifiableNode()
{
    m_name = {};
    m_attributes = {};
    m_attributesStored = {};
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
    return m_attributesStored;
}

void ModifiableNode::SetAttributes(const std::vector<std::shared_ptr<StoredDocumentAttribute>>& newAttributes)
{
    m_attributesStored = newAttributes;

    std::vector<std::shared_ptr<ModifiableAttribute>> attributes;
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributesStored)
    {
        auto modAttribute = std::make_shared<ModifiableAttribute>();
        modAttribute->SetName(attribute->Name());
        modAttribute->SetValue(attribute->Value());
        attributes.emplace_back(modAttribute);
    }
    m_attributes = attributes;
}

const std::shared_ptr<StoredDocumentAttribute> ModifiableNode::Attribute(const std::string& criteria) const
{
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributesStored)
    {
        std::string adjustedName = attribute->Name();
        if (adjustedName == criteria)
        {
            return attribute;
        }
    }

    return {};
}

const std::shared_ptr<StoredDocumentAttribute> ModifiableNode::Attribute(
    const std::string& criteria,
    CaseSensitivity caseSensitive) const
{
    if (caseSensitive == CaseSensitivity::CaseSensitive)
    {
        return Attribute(criteria);
    }

    std::string lowerCriteria = StringHelpers::ToLower(criteria);
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : m_attributesStored)
    {
        std::string adjustedName = attribute->Name();
        if (StringHelpers::ToLower(adjustedName) == lowerCriteria)
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

void ModifiableNode::SetAllChildrenNodes(const std::vector<std::shared_ptr<ModifiableNode>>& allNodes)
{
    if (allNodes.empty())
    {
        m_firstChild = {};
        m_lastChild = {};
    }

    std::shared_ptr<ModifiableNode> last;
    for (const std::shared_ptr<ModifiableNode>& node : allNodes)
    {
        if (last)
        {
            last->SetAdjacentNode(node);
        }

        last = node;
    }

    if (last)
    {
        m_firstChild = allNodes.front();
        if (allNodes.size() > 1)
        {
            m_lastChild = allNodes.back();
        }
        else
        {
            m_lastChild = {};
        }
    }
}

const std::string ModifiableNode::Inner() const
{
    return m_innerText;
}

void ModifiableNode::SetInnerText(const std::string& innerText)
{
    m_innerText = innerText;
}

bool ModifiableNode::Load(const std::shared_ptr<StoredDocumentNode>& storedNode)
{
    if (!storedNode)
    {
        Log::Error("Node is empty when parsing Stored Node into Modifiable Node.",
            "ModifiableNode::Load(std::shared_ptr<StoredDocumentNode>)");
        return false;
    }

    // Set node parameters.
    SetName(storedNode->Name());
    SetInnerText(storedNode->Inner());

    // Copy the attributes
    m_attributes.clear();
    m_attributesStored.clear();
    for (const std::shared_ptr<StoredDocumentAttribute>& attribute : storedNode->Attributes())
    {
        auto modAttribute = std::make_shared<ModifiableAttribute>();
        modAttribute->SetName(attribute->Name());
        modAttribute->SetValue(attribute->Value());
        m_attributes.emplace_back(modAttribute);
        m_attributesStored.emplace_back(modAttribute);
    }

    // Copy all inner nodes.
    std::vector<std::shared_ptr<ModifiableNode>> modifiableNode;
    for (std::shared_ptr<StoredDocumentNode> child = storedNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        auto modNode = std::make_shared<ModifiableNode>();
        if (modNode->Load(child))
        {
            modifiableNode.emplace_back(modNode);
        }
        else
        {
            Log::Error("Could not load a modifiable node from a stored document node.",
                "ModifiableNode::Load(std::shared_ptr<StoredDocumentNode>)");
        }
    }
    SetAllChildrenNodes(modifiableNode);

    return true;
}