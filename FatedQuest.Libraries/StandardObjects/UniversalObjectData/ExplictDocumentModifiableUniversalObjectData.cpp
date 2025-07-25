#include "ExplictDocumentModifiableUniversalObjectData.h"

using namespace FatedQuestLibraries;

ExplictDocumentModifiableUniversalObjectData::ExplictDocumentModifiableUniversalObjectData()
{

}

std::shared_ptr<StoredDocument> ExplictDocumentModifiableUniversalObjectData::ExportToDocument() const
{
    return {};
}

void ExplictDocumentModifiableUniversalObjectData::SetString(const std::string& key, const std::string& value) const
{

}

std::string ExplictDocumentModifiableUniversalObjectData::GetString(const std::string& key) const
{
    return {};
}

bool ExplictDocumentModifiableUniversalObjectData::IsStringLoaded(const std::string& key) const
{
    return {};
}

void ExplictDocumentModifiableUniversalObjectData::SetInt(const std::string& key, int value) const
{
}

int ExplictDocumentModifiableUniversalObjectData::GetInt(const std::string& key) const
{
    return {};
}

bool ExplictDocumentModifiableUniversalObjectData::IsIntLoaded(const std::string& key) const
{
    return {};
}

void ExplictDocumentModifiableUniversalObjectData::SetVector4I(const std::string& key, const FVector4I& value) const
{
}

void ExplictDocumentModifiableUniversalObjectData::SetVector4I(const std::string& key, int x, int y, int z, int w) const
{
}

std::shared_ptr<FVector4I> ExplictDocumentModifiableUniversalObjectData::GetVector4I(const std::string& key) const
{
    return {};
}

bool ExplictDocumentModifiableUniversalObjectData::IsVector4ILoaded(const std::string& key) const
{
    return {};
}
