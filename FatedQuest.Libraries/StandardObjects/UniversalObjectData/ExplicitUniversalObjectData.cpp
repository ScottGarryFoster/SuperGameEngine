#include "ExplicitUniversalObjectData.h"

using namespace FatedQuestLibraries;

ExplicitUniversalObjectData::ExplicitUniversalObjectData(
    const std::shared_ptr<StoredDocument>& document) : DocumentUniversalObjectData(document)
{
}

std::string ExplicitUniversalObjectData::GetString(const std::string& key) const
{
    return DocumentUniversalObjectData::GetString(key);
}

bool ExplicitUniversalObjectData::IsStringLoaded(const std::string& key) const
{
    return DocumentUniversalObjectData::IsStringLoaded(key);
}

int ExplicitUniversalObjectData::GetInt(const std::string& key) const
{
    return DocumentUniversalObjectData::GetInt(key);
}

bool ExplicitUniversalObjectData::IsIntLoaded(const std::string& key) const
{
    return DocumentUniversalObjectData::IsIntLoaded(key);
}

std::shared_ptr<FVector4I> ExplicitUniversalObjectData::GetVector4I(const std::string& key) const
{
    return DocumentUniversalObjectData::GetVector4I(key);
}

bool ExplicitUniversalObjectData::IsVector4ILoaded(const std::string& key) const
{
    return DocumentUniversalObjectData::IsVector4ILoaded(key);
}
