#include "DocumentUniversalObjectData.h"

#include <algorithm>
#include <iterator>

#include "../Logger/Logger/Log.h"
#include "../StandardOperations/Number/IntHelpers.h"
#include "../StandardOperations/Text/StringHelpers.h"
#include "../Position/FVector4I.h"

using namespace FatedQuestLibraries;

DocumentUniversalObjectData::DocumentUniversalObjectData(const std::shared_ptr<StoredDocument>& metaDataDocument)
{
    m_stringValues = {};
    m_intValues = {};
    m_vector4IValues = {};

    std::shared_ptr<StoredDocumentNode> root = metaDataDocument->GetRoot();
    if (!root)
    {
        // Except here?
        return;
    }

    for (std::shared_ptr<StoredDocumentNode> child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "strings")
        {
            ParseStoredDocumentStrings(child);
        }
        else if (nodeName == "ints")
        {
            ParseStoredDocumentInts(child);
        }
        else if (nodeName == "vector4is")
        {
            ParseStoredDocumentVector4I(child);
        }
    }
}

std::vector<std::string> DocumentUniversalObjectData::ListStrings() const
{
    std::vector<std::string> keys;
    keys.reserve(m_stringValues.size());
    std::ranges::transform(m_stringValues, 
                           std::back_inserter(keys),
                           [](const auto& pair) { return pair.first; });
    return keys;
}

std::string DocumentUniversalObjectData::GetString(const std::string& key) const
{
    if (IsStringLoaded(key))
    {
        return m_stringValues.at(key);
    }

    return {};
}

bool DocumentUniversalObjectData::IsStringLoaded(const std::string& key) const
{
    return m_stringValues.contains(key);
}

std::vector<std::string> DocumentUniversalObjectData::ListInts() const
{
    std::vector<std::string> keys;
    keys.reserve(m_intValues.size());
    std::ranges::transform(m_intValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

int DocumentUniversalObjectData::GetInt(const std::string& key) const
{
    if (IsIntLoaded(key))
    {
        return m_intValues.at(key);
    }

    return -1;
}

bool DocumentUniversalObjectData::IsIntLoaded(const std::string& key) const
{
    return m_intValues.contains(key);
}

std::vector<std::string> DocumentUniversalObjectData::ListVector4Is() const
{
    std::vector<std::string> keys;
    keys.reserve(m_vector4IValues.size());
    std::ranges::transform(m_vector4IValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

std::shared_ptr<FVector4I> DocumentUniversalObjectData::GetVector4I(const std::string& key) const
{
    if (IsVector4ILoaded(key))
    {
        return m_vector4IValues.at(key);
    }

    return {};
}

bool DocumentUniversalObjectData::IsVector4ILoaded(const std::string& key) const
{
    return m_vector4IValues.contains(key);
}

void DocumentUniversalObjectData::ParseStoredDocumentStrings(
    const std::shared_ptr<StoredDocumentNode>& stringsNode)
{
    for (std::shared_ptr<StoredDocumentNode> child = stringsNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "string")
        {
            ParseStoredDocumentSingleString(child);
        }
        else
        {
            Log::Error("When parsing a game asset file, found a string not called \"String\", potential file corruption.",
                "SuperGameAsset::ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
        }
    }
}

void DocumentUniversalObjectData::ParseStoredDocumentSingleString(
    const std::shared_ptr<StoredDocumentNode>& stringNode)
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

    std::string newValue = {};
    if (std::shared_ptr<StoredDocumentAttribute> attribute =
        stringNode->Attribute("value", CaseSensitivity::IgnoreCase))
    {
        std::string value = StringHelpers::Trim(attribute->Value());
        if (!value.empty())
        {
            newValue = value;
        }
    }

    if (!newKey.empty() && !newValue.empty())
    {
        m_stringValues.insert_or_assign(newKey, newValue);
    }
}

void DocumentUniversalObjectData::ParseStoredDocumentInts(
    const std::shared_ptr<StoredDocumentNode>& intsNode)
{
    for (std::shared_ptr<StoredDocumentNode> child = intsNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "int")
        {
            ParseStoredDocumentSingleInt(child);
        }
        else
        {
            Log::Error("When parsing a game asset file, found a string not called \"Int\", potential file corruption.",
                "SuperGameAsset::ParseStoredDocumentInts(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
        }
    }
}

void DocumentUniversalObjectData::ParseStoredDocumentSingleInt(
    const std::shared_ptr<StoredDocumentNode>& intNode)
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

    if (!newKey.empty() && foundValue)
    {
        m_intValues.insert_or_assign(newKey, newValue);
    }
}

void DocumentUniversalObjectData::ParseStoredDocumentVector4I(
    const std::shared_ptr<StoredDocumentNode>& node)
{
    for (std::shared_ptr<StoredDocumentNode> child = node->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "vector4i")
        {
            ParseStoredDocumentSingleVector4I(child);
        }
        else
        {
            Log::Error("When parsing a game asset file, found a string not called \"Vector4i\", potential file corruption.",
                "SuperGameAsset::ParseStoredDocumentVector4I(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>)");
        }
    }
}

void DocumentUniversalObjectData::ParseStoredDocumentSingleVector4I(
    const std::shared_ptr<StoredDocumentNode>& node)
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

    if (!newKey.empty() && foundValueX && foundValueY && foundValueZ && foundValueW)
    {
        auto newVector = std::make_shared<FVector4I>(xValue, yValue, zValue, wValue);
        m_vector4IValues.insert_or_assign(newKey, newVector);
    }
}
