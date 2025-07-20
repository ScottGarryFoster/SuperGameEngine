#include "ToolsAssetTemplate.h"
#include "../../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetTemplate::ToolsAssetTemplate(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& documentNode)
{
}

ToolsAssetTemplate::~ToolsAssetTemplate()
{
}

bool ToolsAssetTemplate::ShouldUseTemplate(const std::string& filepath) const
{
    return false;
}

std::string ToolsAssetTemplate::CreateAssetFile(const std::string& filepath) const
{
    return std::string();
}
