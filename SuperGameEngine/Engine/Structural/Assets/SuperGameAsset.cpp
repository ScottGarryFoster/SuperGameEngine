#include "SuperGameAsset.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperGameAsset::SuperGameAsset(const std::shared_ptr<StoredDocument>& universalObject, const std::string& path) : DocumentUniversalObjectData(universalObject)
{
    m_name = GetString("GameAssetName");
    m_path = path;
}

std::string SuperGameAsset::GetName() const
{
    return m_name;
}

std::string SuperGameEngine::SuperGameAsset::GetPath() const
{
    return m_path;
}
