#include "ExplictDocumentModifiableUniversalObjectData.h"

#include <algorithm>
#include <iterator>

#include "ModifiableDocument.h"
#include "Position/FVector4I.h"

using namespace FatedQuestLibraries;

ExplictDocumentModifiableUniversalObjectData::ExplictDocumentModifiableUniversalObjectData()
{
    isDirty = true;
    m_modifiableDocument = std::make_shared<ModifiableDocument>();
}

std::shared_ptr<StoredDocument> ExplictDocumentModifiableUniversalObjectData::ExportToDocument() const
{
    if (isDirty)
    {
        
    }

    return m_modifiableDocument;
}

std::vector<std::string> ExplictDocumentModifiableUniversalObjectData::ListStrings() const
{
    std::vector<std::string> keys;
    keys.reserve(m_stringValues.size());
    std::ranges::transform(m_stringValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

void ExplictDocumentModifiableUniversalObjectData::SetString(const std::string& key, const std::string& value)
{
    isDirty = true;

    m_stringValues.insert_or_assign(key, value);
}

std::string ExplictDocumentModifiableUniversalObjectData::GetString(const std::string& key) const
{
    if (m_stringValues.contains(key))
    {
        return m_stringValues.at(key);
    }

    return {};
}

bool ExplictDocumentModifiableUniversalObjectData::IsStringLoaded(const std::string& key) const
{
    return m_stringValues.contains(key);
}

std::vector<std::string> ExplictDocumentModifiableUniversalObjectData::ListInts() const
{
    std::vector<std::string> keys;
    keys.reserve(m_intValues.size());
    std::ranges::transform(m_intValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

void ExplictDocumentModifiableUniversalObjectData::SetInt(const std::string& key, int value)
{
    isDirty = true;

    m_intValues.insert_or_assign(key, value);
}

int ExplictDocumentModifiableUniversalObjectData::GetInt(const std::string& key) const
{
    if (m_intValues.contains(key))
    {
        return m_intValues.at(key);
    }

    return -1;
}

bool ExplictDocumentModifiableUniversalObjectData::IsIntLoaded(const std::string& key) const
{
    return m_intValues.contains(key);
}

std::vector<std::string> ExplictDocumentModifiableUniversalObjectData::ListVector4Is() const
{
    std::vector<std::string> keys;
    keys.reserve(m_vector4IValues.size());
    std::ranges::transform(m_vector4IValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

void ExplictDocumentModifiableUniversalObjectData::SetVector4I(const std::string& key, const FVector4I& value)
{
    isDirty = true;

    m_vector4IValues.insert_or_assign(key, std::make_shared<FVector4I>(value));
}

void ExplictDocumentModifiableUniversalObjectData::SetVector4I(const std::string& key, int x, int y, int z, int w)
{
    isDirty = true;

    m_vector4IValues.insert_or_assign(key, std::make_shared<FVector4I>(x, y, z, w));
}

std::shared_ptr<FVector4I> ExplictDocumentModifiableUniversalObjectData::GetVector4I(const std::string& key) const
{
    if (m_vector4IValues.contains(key))
    {
        return m_vector4IValues.at(key);
    }

    return {};
}

bool ExplictDocumentModifiableUniversalObjectData::IsVector4ILoaded(const std::string& key) const
{
    return m_vector4IValues.contains(key);
}
