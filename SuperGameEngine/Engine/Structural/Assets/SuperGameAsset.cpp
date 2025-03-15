#include "SuperGameAsset.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperGameAsset::SuperGameAsset(const std::shared_ptr<StoredDocument>& metaDataDocument)
{
    m_stringValues = {};
    m_intValues = {};
    m_name = {};

    std::shared_ptr<StoredDocumentNode> root = metaDataDocument->GetRoot();
    if (!root)
    {
        // Except here?
        return;
    }

    for (std::shared_ptr<StoredDocumentNode> child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "gameassetmeta")
        {
            ParseStoredDocumentGameAssetMetadata(child);
        }
        else if (nodeName == "strings")
        {
            ParseStoredDocumentStrings(child);
        }
        else if (nodeName == "ints")
        {
            ParseStoredDocumentInts(child);
        }
    }
}

std::string SuperGameAsset::GetName() const
{
    return m_name;
}

std::string SuperGameAsset::GetString(const std::string& key)
{
    if (IsStringLoaded(key))
    {
        return m_stringValues[key];
    }

    return {};
}

bool SuperGameAsset::IsStringLoaded(const std::string& key)
{
    return m_stringValues.contains(key);
}

int SuperGameAsset::GetInt(const std::string& key)
{
    if (IsIntLoaded(key))
    {
        return m_intValues[key];
    }

    return {};
}

bool SuperGameAsset::IsIntLoaded(const std::string& key)
{
    return m_intValues.contains(key);
}

void SuperGameAsset::ParseStoredDocumentGameAssetMetadata(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& gameAssetNode)
{
    if (std::shared_ptr<StoredDocumentAttribute> attribute = 
        gameAssetNode->Attribute("name", CaseSensitivity::IgnoreCase))
    {
        std::string name = StringHelpers::Trim(attribute->Value());
        if (!name.empty())
        {
            m_name = name;
        }
    }
}

void SuperGameAsset::ParseStoredDocumentStrings(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringsNode)
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

void SuperGameAsset::ParseStoredDocumentSingleString(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringNode)
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

void SuperGameAsset::ParseStoredDocumentInts(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intsNode)
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

void SuperGameAsset::ParseStoredDocumentSingleInt(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intNode)
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