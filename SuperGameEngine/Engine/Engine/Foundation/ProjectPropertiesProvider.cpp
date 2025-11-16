#include "ProjectPropertiesProvider.h"

#include "ProjectProperties.h"
#include "SuperProjectProperties.h"
#include "../../../../FatedQuest.Libraries/GamePackage/AllReferences.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

std::shared_ptr<ProjectProperties> ProjectPropertiesProvider::LoadProjectProperties(
    const std::shared_ptr<GamePackage>& gamePackage) const
{
    std::string relativePath = {};
    if (gamePackage->File()->Exists(m_prjectPropertiesFileName))
    {
        relativePath = m_prjectPropertiesFileName;
    }
    else
    {
        for (const std::string& name : gamePackage->Directory()->ListDirectoryNames({}))
        {
            if (gamePackage->File()->Exists(name + "\\" + m_prjectPropertiesFileName))
            {
                relativePath = name + "\\" + m_prjectPropertiesFileName;
            }
        }
    }

    if (relativePath.empty())
    {
        Log::Error("Could not find a project properties file. Ensure it is in either the root or one directory deep.");
        return {};
    }

    auto document = std::make_shared<RapidXMLDocument>();
    if (!document->Load(gamePackage->File()->ReadFileContents(relativePath)))
    {
        Log::Error("Could not find a project properties file. Could not parse the file: " + relativePath);
        return {};
    }

    return std::make_shared<SuperProjectProperties>(document);
}
