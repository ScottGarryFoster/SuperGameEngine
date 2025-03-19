#include "ExplicitUniversalObjectData.h"

using namespace FatedQuestLibraries;

ExplicitUniversalObjectData::ExplicitUniversalObjectData(
    const std::shared_ptr<StoredDocument>& document) : DocumentUniversalObjectData(document)
{
}

std::string ExplicitUniversalObjectData::GetString(const std::string& key)
{
    return DocumentUniversalObjectData::GetString(key);
}

bool ExplicitUniversalObjectData::IsStringLoaded(const std::string& key)
{
    return DocumentUniversalObjectData::IsStringLoaded(key);
}

int ExplicitUniversalObjectData::GetInt(const std::string& key)
{
    return DocumentUniversalObjectData::GetInt(key);
}

bool ExplicitUniversalObjectData::IsIntLoaded(const std::string& key)
{
    return DocumentUniversalObjectData::IsIntLoaded(key);
}
