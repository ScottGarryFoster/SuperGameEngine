#include "ToolsAssetTemplateProvider.h"
#include "FatedQuestLibraries.h"
#include "../../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "LayoutEditors/ToolsAssetLayoutEditorFactory.h"
#include "Template/ToolsAssetMetaData.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetTemplateProvider::ToolsAssetTemplateProvider(
    const std::shared_ptr<GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
    m_assetLayoutEditorFactory = std::make_shared<ToolsAssetLayoutEditorFactory>();
}

std::vector<std::shared_ptr<const AssetMetaData>>
    ToolsAssetTemplateProvider::GetAssetTemplates() const
{
    return m_assetTemplates;
}

bool ToolsAssetTemplateProvider::LoadAllAssetMeta()
{
    if (!m_gamePackage->Directory()->Exists(m_assetTemplateFolder))
    {
        Log::Error("No Asset Template folder. Cannot create asset templates automatically.",
            "ToolsAssetTemplateProvider::LoadAllAssetMeta");
        return false;
    }

    bool loadedSuccessfully = true;
    std::vector<std::string> templateFilenames = m_gamePackage->Directory()->GetFiles(m_assetTemplateFolder);
    for (const std::string& templateFilename : templateFilenames)
    {
        std::string fullGamepackagePath = Directory::CombinePath(m_assetTemplateFolder, templateFilename);
        std::string fileContents = m_gamePackage->File()->ReadFileContents(fullGamepackagePath);

        auto document = std::make_shared<RapidXMLDocument>();
        if (!document->Load(fileContents))
        {
            Log::Error("Could not load asset template file: " + fullGamepackagePath,
                "ToolsAssetTemplateProvider::LoadAllAssetMeta");
            continue;
        }

        try
        {
            m_assetTemplates.emplace_back(std::make_shared<ToolsAssetMetaData>(document, m_assetLayoutEditorFactory));
        }
        catch (Exception& e)
        {
            Log::Exception("Could not load template file due to an exception." +
                e.Message() + " Filepath: " + fullGamepackagePath,
                "ToolsAssetTemplateProvider::LoadAllAssetMeta",
                e.Type());
            loadedSuccessfully = false;
        }
    }

    return loadedSuccessfully;
}
