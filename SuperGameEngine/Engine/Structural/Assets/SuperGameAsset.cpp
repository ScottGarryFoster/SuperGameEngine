#include "SuperGameAsset.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperGameAsset::SuperGameAsset(const std::shared_ptr<StoredDocument>& universalObject) : DocumentUniversalObjectData(universalObject)
{
    m_name = DocumentUniversalObjectData::GetString("GameAssetName");
}

std::string SuperGameAsset::GetName() const
{
    return m_name;
}