#include "DocumentUniversalObjectData.h"

#include <algorithm>
#include <iterator>

#include "UniversalObjectParser.h"
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

    m_parser = std::make_shared<UniversalObjectParser>();
    for (std::shared_ptr<StoredDocumentNode> child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string nodeName = StringHelpers::ToLower(child->Name());
        if (nodeName == "strings")
        {
            m_stringValues = m_parser->ParseStoredDocumentStrings(child);
        }
        else if (nodeName == "ints")
        {
            m_intValues = m_parser->ParseStoredDocumentInts(child);
        }
        else if (nodeName == "vector4is")
        {
            m_vector4IValues = m_parser->ParseStoredDocumentVector4I(child);
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