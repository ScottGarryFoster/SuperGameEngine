#include "UniversalObjectParser.h"

#include "ModifiableAttribute.h"
#include "ModifiableNode.h"
#include "StoredDocumentNode.h"
#include "../../Logger/Logger/Log.h"
#include "Number/IntHelpers.h"
#include "Position/FVector4I.h"
#include "Text/StringHelpers.h"

using namespace FatedQuestLibraries;

std::shared_ptr<ModifiableNode> UniversalObjectParser::CreateStringsNode(
    const std::unordered_map<std::string, std::string>& strings) const
{
    std::vector<std::shared_ptr<ModifiableNode>> stringNodes;
    for (const auto& string : strings)
    {
        auto stringNode = CreateStringNode(string.first, string.second);
        if (stringNode)
        {
            stringNodes.emplace_back(stringNode);
        }
    }

    if (!stringNodes.empty())
    {
        auto node = std::make_shared<ModifiableNode>();
        node->SetName("Strings");
        node->SetAllChildrenNodes(stringNodes);
        return node;
    }

    return {};
}

std::shared_ptr<ModifiableNode> UniversalObjectParser::CreateStringNode(
    const std::string& key,
    const std::string& value) const
{
    if (key.empty() || value.empty())
    {
        return {};
    }

    auto node = std::make_shared<ModifiableNode>();
    node->SetName("String");

    std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
    auto keyAttribute = std::make_shared<ModifiableAttribute>();
    keyAttribute->SetName("Key");
    keyAttribute->SetValue(key);
    attributes.emplace_back(keyAttribute);

    auto valueAttribute = std::make_shared<ModifiableAttribute>();
    valueAttribute->SetName("Value");
    valueAttribute->SetValue(value);
    attributes.emplace_back(valueAttribute);

    node->SetAttributes(attributes);
    return node;
}

std::unordered_map<std::string, std::string>
    UniversalObjectParser::ParseStoredDocumentStrings(
    const std::shared_ptr<StoredDocumentNode>& stringsNode) const
{
    std::unordered_map<std::string, std::string> extractedValues;
    for (std::shared_ptr<StoredDocumentNode> child = stringsNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "string")
        {
            std::pair<std::string, std::string> parsed = ParseStoredDocumentSingleString(child);
            if (!parsed.first.empty())
            {
                extractedValues.insert_or_assign(parsed.first, parsed.second);
            }
            else
            {
                Log::Error("When parsing a universal object file, found a string with an empty key.",
                    "UniversalObjectParser::ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
            }
        }
        else
        {
            Log::Error("When parsing a game asset file, found a string not called \"String\", potential file corruption.",
                "UniversalObjectParser::ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
        }
    }

    return extractedValues;
}

std::pair<std::string, std::string>
    UniversalObjectParser::ParseStoredDocumentSingleString(
    const std::shared_ptr<StoredDocumentNode>& stringNode) const
{
    std::string newKey = {};
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        stringNode->Attribute("key", CaseSensitivity::IgnoreCase))
    {
        std::string key = StringHelpers::Trim(attribute->Value());
        if (!key.empty())
        {
            newKey = key;
        }
    }

    bool foundValue = false;
    std::string newValue = {};
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        stringNode->Attribute("value", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            newValue = value;
            foundValue = true;
        }
    }

    if (!foundValue)
    {
        newKey = {};
    }

    return { newKey, newValue };
}

std::shared_ptr<ModifiableNode> UniversalObjectParser::CreateIntsNode(
    const std::unordered_map<std::string, int>& ints) const
{
    std::vector<std::shared_ptr<ModifiableNode>> currentNodes;
    for (const auto& current : ints)
    {
        auto currentNode = CreateIntNode(current.first, current.second);
        if (currentNode)
        {
            currentNodes.emplace_back(currentNode);
        }
    }

    if (!currentNodes.empty())
    {
        auto node = std::make_shared<ModifiableNode>();
        node->SetName("Ints");
        node->SetAllChildrenNodes(currentNodes);
        return node;
    }

    return {};
}

std::shared_ptr<ModifiableNode> UniversalObjectParser::CreateIntNode(
    const std::string& key,
    const int& value) const
{
    if (key.empty())
    {
        return {};
    }

    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Int");

    std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
    auto keyAttribute = std::make_shared<ModifiableAttribute>();
    keyAttribute->SetName("Key");
    keyAttribute->SetValue(key);
    attributes.emplace_back(keyAttribute);

    auto valueAttribute = std::make_shared<ModifiableAttribute>();
    valueAttribute->SetName("Value");
    valueAttribute->SetValue(std::to_string(value));
    attributes.emplace_back(valueAttribute);

    node->SetAttributes(attributes);
    return node;
}

std::unordered_map<std::string, int>
    UniversalObjectParser::ParseStoredDocumentInts(
    const std::shared_ptr<StoredDocumentNode>& intsNode) const
{
    std::unordered_map<std::string, int> extractedValues;
    for (std::shared_ptr<StoredDocumentNode> child = intsNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "int")
        {
            std::pair<std::string, int> parsed = ParseStoredDocumentSingleInt(child);
            if (!parsed.first.empty())
            {
                extractedValues.insert_or_assign(parsed.first, parsed.second);
            }
            else
            {
                Log::Error("When parsing a universal object file, found a int with an empty key.",
                    "UniversalObjectParser::ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
            }
        }
        else
        {
            Log::Error("When parsing a game asset file, found a string not called \"Int\", potential file corruption.",
                "UniversalObjectParser::ParseStoredDocumentInts(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
        }
    }

    return extractedValues;
}

std::pair<std::string, int>
    UniversalObjectParser::ParseStoredDocumentSingleInt(
    const std::shared_ptr<StoredDocumentNode>& intNode) const
{
    std::string newKey = {};
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        intNode->Attribute("key", CaseSensitivity::IgnoreCase))
    {
        std::string key = StringHelpers::Trim(attribute->Value());
        if (!key.empty())
        {
            newKey = key;
        }
    }

    int newValue = -1;
    bool foundValue = false;
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        intNode->Attribute("value", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            int outValue = -1;
            if (IntHelpers::TryParse(value, outValue))
            {
                newValue = outValue;
                foundValue = true;
            }
        }
    }

    if (!foundValue)
    {
        newKey = {};
    }

    return { newKey, newValue };
}

std::shared_ptr<FatedQuestLibraries::ModifiableNode> UniversalObjectParser::CreateVector4IsNode(
    const std::unordered_map<std::string, std::shared_ptr<FVector4I>>& vector4Is) const
{
    std::vector<std::shared_ptr<ModifiableNode>> currentNodes;
    for (const auto& current : vector4Is)
    {
        auto currentNode = CreateVector4INode(current.first, current.second);
        if (currentNode)
        {
            currentNodes.emplace_back(currentNode);
        }
    }

    if (!currentNodes.empty())
    {
        auto node = std::make_shared<ModifiableNode>();
        node->SetName("Vector4Is");
        node->SetAllChildrenNodes(currentNodes);
        return node;
    }

    return {};
}

std::shared_ptr<FatedQuestLibraries::ModifiableNode> UniversalObjectParser::CreateVector4INode(const std::string& key,
    const std::shared_ptr<FVector4I>& value) const
{
    if (key.empty() || !value)
    {
        return {};
    }

    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Vector4I");

    std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
    auto keyAttribute = std::make_shared<ModifiableAttribute>();
    keyAttribute->SetName("Key");
    keyAttribute->SetValue(key);
    attributes.emplace_back(keyAttribute);

    auto xAttribute = std::make_shared<ModifiableAttribute>();
    xAttribute->SetName("X");
    xAttribute->SetValue(std::to_string(value->GetX()));
    attributes.emplace_back(xAttribute);

    auto yAttribute = std::make_shared<ModifiableAttribute>();
    yAttribute->SetName("Y");
    yAttribute->SetValue(std::to_string(value->GetY()));
    attributes.emplace_back(yAttribute);

    auto zAttribute = std::make_shared<ModifiableAttribute>();
    zAttribute->SetName("Z");
    zAttribute->SetValue(std::to_string(value->GetZ()));
    attributes.emplace_back(zAttribute);

    auto wAttribute = std::make_shared<ModifiableAttribute>();
    wAttribute->SetName("W");
    wAttribute->SetValue(std::to_string(value->GetW()));
    attributes.emplace_back(wAttribute);

    node->SetAttributes(attributes);
    return node;
}

std::unordered_map<std::string, std::shared_ptr<FVector4I>>
    UniversalObjectParser::ParseStoredDocumentVector4I(
    const std::shared_ptr<StoredDocumentNode>& node) const
{
    std::unordered_map<std::string, std::shared_ptr<FVector4I>> extractedValues;
    for (std::shared_ptr<StoredDocumentNode> child = node->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "vector4i")
        {
            std::pair<std::string, std::shared_ptr<FVector4I>> parsed = ParseStoredDocumentSingleVector4I(child);
            if (!parsed.first.empty())
            {
                extractedValues.insert_or_assign(parsed.first, parsed.second);
            }
            else
            {
                Log::Error("When parsing a universal object file, found a vector4i with an empty key.",
                    "UniversalObjectParser::ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
            }
        }
        else
        {
            Log::Error("When parsing a game asset file, found a string not called \"Vector4i\", potential file corruption.",
                "UniversalObjectParser::ParseStoredDocumentVector4I(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
        }
    }

    return extractedValues;
}

std::pair<std::string, std::shared_ptr<FVector4I>>
    UniversalObjectParser::ParseStoredDocumentSingleVector4I(
    const std::shared_ptr<StoredDocumentNode>& node) const
{
    std::string newKey = {};
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("key", CaseSensitivity::IgnoreCase))
    {
        std::string key = StringHelpers::Trim(attribute->Value());
        if (!key.empty())
        {
            newKey = key;
        }
    }

    if (newKey.empty())
    {
        // Early out, no key no parse.
        return { {}, {} };
    }

    int xValue = -1;
    bool foundValueX = false;
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("x", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            int outValue = -1;
            if (IntHelpers::TryParse(value, outValue))
            {
                xValue = outValue;
                foundValueX = true;
            }
        }
    }

    if (!foundValueX)
    {
        // Early out, no key no parse.
        return { {}, {} };
    }

    int yValue = -1;
    bool foundValueY = false;
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("y", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            int outValue = -1;
            if (IntHelpers::TryParse(value, outValue))
            {
                yValue = outValue;
                foundValueY = true;
            }
        }
    }

    if (!foundValueY)
    {
        // Early out, no key no parse.
        return { {}, {} };
    }

    int zValue = -1;
    bool foundValueZ = false;
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("z", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            int outValue = -1;
            if (IntHelpers::TryParse(value, outValue))
            {
                zValue = outValue;
                foundValueZ = true;
            }
        }
    }

    if (!foundValueZ)
    {
        // Early out, no key no parse.
        return { {}, {} };
    }

    int wValue = -1;
    bool foundValueW = false;
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("w", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            int outValue = -1;
            if (IntHelpers::TryParse(value, outValue))
            {
                wValue = outValue;
                foundValueW = true;
            }
        }
    }

    if (!foundValueW)
    {
        // Early out, no key no parse.
        return { {}, {} };
    }

    return { newKey, std::make_shared<FVector4I>(xValue, yValue, zValue, wValue) };
}
