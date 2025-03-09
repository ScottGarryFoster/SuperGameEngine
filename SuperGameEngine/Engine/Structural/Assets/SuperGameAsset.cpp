#include "SuperGameAsset.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperGameAsset::SuperGameAsset(const std::shared_ptr<StoredDocument>& metaDataDocument)
{
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
    }
}

std::string SuperGameAsset::GetName() const
{
    return m_name;
}

void SuperGameAsset::ParseStoredDocumentGameAssetMetadata(
    const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& storedDocumentNode)
{
    if (std::shared_ptr<StoredDocumentAttribute> attribute = 
        storedDocumentNode->Attribute("name", CaseSensitivity::IgnoreCase))
    {
        std::string name = StringHelpers::Trim(attribute->Value());
        if (!name.empty())
        {
            m_name = name;
        }
    }
}
