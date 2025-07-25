#include "UniversalObjectParser.h"

#include "StoredDocumentNode.h"
#include "../../Logger/Logger/Log.h"
#include "Number/IntHelpers.h"
#include "Position/FVector4I.h"
#include "Text/StringHelpers.h"

using namespace FatedQuestLibraries;

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
