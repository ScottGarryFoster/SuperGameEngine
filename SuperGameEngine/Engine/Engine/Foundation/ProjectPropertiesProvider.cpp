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
    std::string relativePath = GetProjectPropertiesPath(gamePackage);
    if (relativePath.empty())
    {
        Log::Error("Could not find a project properties file. Ensure it is in either the root or one directory deep.");
        return {};
    }

    // TODO: [#227] Project properties is not always going to be XML. Ensure this can be loaded binary.
    auto document = std::make_shared<RapidXMLDocument>();
    if (!document->Load(gamePackage->File()->ReadFileContents(relativePath)))
    {
        Log::Error("Could not find a project properties file. Could not parse the file: " + relativePath);
        return {};
    }

    return CreateProjectProperties(document);
}

bool ProjectPropertiesProvider::CanLoadProjectProperties(const std::shared_ptr<GamePackage>& gamePackage) const
{
    if (gamePackage->File()->Exists(m_projectPropertiesFileName))
    {
        return true;
    }

    for (const std::string& name : gamePackage->Directory()->ListDirectoryNames({}))
    {
        if (gamePackage->File()->Exists(name + "\\" + m_projectPropertiesFileName))
        {
            return true;
        }
    }

    return false;
}

std::string ProjectPropertiesProvider::GetProjectPropertiesPath(
    const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage) const
{
    std::string relativePath = {};
    if (gamePackage->File()->Exists(m_projectPropertiesFileName))
    {
        relativePath = m_projectPropertiesFileName;
    }
    else
    {
        for (const std::string& name : gamePackage->Directory()->ListDirectoryNames({}))
        {
            if (gamePackage->File()->Exists(name + "\\" + m_projectPropertiesFileName))
            {
                relativePath = name + "\\" + m_projectPropertiesFileName;
            }
        }
    }

    return relativePath;
}

std::shared_ptr<ProjectProperties> ProjectPropertiesProvider::CreateProjectProperties(
    const std::shared_ptr<StoredDocument>& storedDocument) const
{
    return std::make_shared<SuperProjectProperties>(storedDocument);
}
