#include "ExplicitTextGameAsset.h"

using namespace SuperGameEngine;

ExplicitTextGameAsset::ExplicitTextGameAsset(
    const std::shared_ptr<FatedQuestLibraries::StoredDocument>& metaDataDocument)
    : SuperGameAsset(metaDataDocument)
{

}

std::string ExplicitTextGameAsset::GetString(const std::string& key)
{
    return SuperGameAsset::GetString(key);
}

bool ExplicitTextGameAsset::IsStringLoaded(const std::string& key)
{
    return SuperGameAsset::IsStringLoaded(key);
}

int ExplicitTextGameAsset::GetInt(const std::string& key)
{
    return SuperGameAsset::GetInt(key);
}

bool ExplicitTextGameAsset::IsIntLoaded(const std::string& key)
{
    return SuperGameAsset::IsIntLoaded(key);
}
