#include "ExplicitDocumentModifiableUniversalObjectData.h"

#include <algorithm>
#include <iterator>

#include "ModifiableDocument.h"
#include "ModifiableNode.h"
#include "UniversalObjectParser.h"
#include "Position/FVector4I.h"
#include "Text/StringHelpers.h"
#include "../Logger/AllReferences.h"
#include "Object/GUID/GUIDHelpers.h"

using namespace FatedQuestLibraries;

ExplicitDocumentModifiableUniversalObjectData::ExplicitDocumentModifiableUniversalObjectData()
{
    m_isDirty = false;
    m_modifiableDocument = std::make_shared<ModifiableDocument>();
    m_parser = std::make_shared<UniversalObjectParser>();
    m_guid = GUIDHelpers::CreateGUID();
}

std::shared_ptr<ModifiableDocument> ExplicitDocumentModifiableUniversalObjectData::ExportToDocument()
{
    if (m_isDirty || !m_modifiableDocument)
    {
        m_modifiableDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName("UniversalObjectData");

        std::vector<std::shared_ptr<ModifiableNode>> children;
        if (auto node = m_parser->CreateStringsNode(m_stringValues))
        {
            children.emplace_back(node);
        }

        if (auto node = m_parser->CreateIntsNode(m_intValues))
        {
            children.emplace_back(node);
        }

        if (auto node = m_parser->CreateVector4IsNode(m_vector4IValues))
        {
            children.emplace_back(node);
        }

        root->SetAllChildrenNodes(children);
        m_modifiableDocument->SetRootElement(root);
    }

    return m_modifiableDocument;
}

bool ExplicitDocumentModifiableUniversalObjectData::ImportAsDocument(const std::shared_ptr<StoredDocument>& document)
{
    m_stringValues = {};
    m_intValues = {};
    m_vector4IValues = {};

    std::shared_ptr<StoredDocumentNode> root = document->GetRoot();
    if (!root)
    {
        Log::Error("No root found when importing universal object data.",
            "ExplicitDocumentModifiableUniversalObjectData::ImportAsDocument(const std::shared_ptr<StoredDocument>&)");
        return false;
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

    m_isDirty = false;
    return true;
}

std::shared_ptr<Guid> ExplicitDocumentModifiableUniversalObjectData::GetGuid() const
{
    return m_guid;
}

bool ExplicitDocumentModifiableUniversalObjectData::IsDirty() const
{
    return m_isDirty;
}

std::vector<std::string> ExplicitDocumentModifiableUniversalObjectData::ListStrings() const
{
    std::vector<std::string> keys;
    keys.reserve(m_stringValues.size());
    std::ranges::transform(m_stringValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

void ExplicitDocumentModifiableUniversalObjectData::SetString(const std::string& key, const std::string& value)
{
    m_isDirty = true;

    m_stringValues.insert_or_assign(key, value);
}

bool ExplicitDocumentModifiableUniversalObjectData::UnsetString(const std::string& key)
{
    if (m_stringValues.contains(key))
    {
        m_stringValues.erase(key);
        return true;
    }

    return false;
}

std::string ExplicitDocumentModifiableUniversalObjectData::GetString(const std::string& key) const
{
    if (m_stringValues.contains(key))
    {
        return m_stringValues.at(key);
    }

    return {};
}

bool ExplicitDocumentModifiableUniversalObjectData::IsStringLoaded(const std::string& key) const
{
    return m_stringValues.contains(key);
}

std::vector<std::string> ExplicitDocumentModifiableUniversalObjectData::ListInts() const
{
    std::vector<std::string> keys;
    keys.reserve(m_intValues.size());
    std::ranges::transform(m_intValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

void ExplicitDocumentModifiableUniversalObjectData::SetInt(const std::string& key, int value)
{
    m_isDirty = true;

    m_intValues.insert_or_assign(key, value);
}

bool ExplicitDocumentModifiableUniversalObjectData::UnsetInt(const std::string& key)
{
    if (m_intValues.contains(key))
    {
        m_intValues.erase(key);
        return true;
    }

    return false;
}

int ExplicitDocumentModifiableUniversalObjectData::GetInt(const std::string& key) const
{
    if (m_intValues.contains(key))
    {
        return m_intValues.at(key);
    }

    return -1;
}

bool ExplicitDocumentModifiableUniversalObjectData::IsIntLoaded(const std::string& key) const
{
    return m_intValues.contains(key);
}

std::vector<std::string> ExplicitDocumentModifiableUniversalObjectData::ListVector4Is() const
{
    std::vector<std::string> keys;
    keys.reserve(m_vector4IValues.size());
    std::ranges::transform(m_vector4IValues,
        std::back_inserter(keys),
        [](const auto& pair) { return pair.first; });
    return keys;
}

bool ExplicitDocumentModifiableUniversalObjectData::UnsetVector4I(const std::string& key)
{
    if (m_vector4IValues.contains(key))
    {
        m_vector4IValues.erase(key);
        return true;
    }

    return false;
}

void ExplicitDocumentModifiableUniversalObjectData::SetVector4I(const std::string& key, const FVector4I& value)
{
    m_isDirty = true;

    m_vector4IValues.insert_or_assign(key, std::make_shared<FVector4I>(value));
}

void ExplicitDocumentModifiableUniversalObjectData::SetVector4I(const std::string& key, int x, int y, int z, int w)
{
    m_isDirty = true;

    m_vector4IValues.insert_or_assign(key, std::make_shared<FVector4I>(x, y, z, w));
}

std::shared_ptr<FVector4I> ExplicitDocumentModifiableUniversalObjectData::GetVector4I(const std::string& key) const
{
    if (m_vector4IValues.contains(key))
    {
        return m_vector4IValues.at(key);
    }

    return {};
}

bool ExplicitDocumentModifiableUniversalObjectData::IsVector4ILoaded(const std::string& key) const
{
    return m_vector4IValues.contains(key);
}
