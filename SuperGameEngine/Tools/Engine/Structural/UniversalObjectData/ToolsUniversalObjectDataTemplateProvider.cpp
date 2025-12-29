#include "ToolsUniversalObjectDataTemplateProvider.h"

#include "../../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "LayoutEditors/ToolsAssetLayoutEditorFactory.h"
#include "../../../../../FatedQuest.Libraries/GamePackage/AllReferences.h"
#include "../../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "../../../../../FatedQuest.Libraries/XmlDocument/AllReferences.h"
#include "../../../../../FatedQuest.Libraries/Exceptions/AllReferences.h"
#include "Template/ToolsUniversalMetaData.h"

using namespace FatedQuestLibraries;

SuperGameTools::ToolsUniversalObjectDataTemplateProvider::ToolsUniversalObjectDataTemplateProvider(
    const std::shared_ptr<GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
    m_layoutEditorFactory = std::make_shared<ToolsAssetLayoutEditorFactory>();
}

std::vector<std::shared_ptr<const SuperGameTools::SingleLayoutMetaData>>
    SuperGameTools::ToolsUniversalObjectDataTemplateProvider::GetAssetTemplates() const
{
    return m_objectTemplates;
}

bool SuperGameTools::ToolsUniversalObjectDataTemplateProvider::LoadAllAssetMeta()
{
    if (!m_gamePackage->Directory()->Exists(m_templateFolder))
    {
        Log::Error("No Asset Template folder. Cannot create asset templates automatically.",
            "ToolsAssetTemplateProvider::LoadAllAssetMeta");
        return false;
    }

    bool loadedSuccessfully = true;
    std::vector<std::string> templateFilenames = m_gamePackage->Directory()->GetFiles(m_templateFolder);
    for (const std::string& templateFilename : templateFilenames)
    {
        std::string fullGamepackagePath = Directory::CombinePath(m_templateFolder, templateFilename);
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
            m_objectTemplates.emplace_back(std::make_shared<ToolsUniversalMetaData>(document, m_layoutEditorFactory));
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
