#pragma once
#include <memory>

#include "AssetLayout.h"


namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

namespace SuperGameTools
{
    /// <summary>
    /// Describes how to edit the given asset and how the data is laid out.
    /// </summary>
    class ToolsAssetLayout : public AssetLayout
    {
    public:

        ToolsAssetLayout(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode);
    };
}
