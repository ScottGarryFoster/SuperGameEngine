#include "ToolsSceneLoader.h"
#include "../../FatedQuestLibraries.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/ModifiableDocument.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsSceneLoader::ToolsSceneLoader(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

std::shared_ptr<ModifiableDocument> ToolsSceneLoader::LoadScene(const std::string& filepath)
{
    std::string path = File::Sanitize(filepath);
    if (!m_gamePackage->File()->Exists(path))
    {
        Log::Error("File does not exist. Filepath: " + path, 
            "ToolsSceneLoader::LoadScene(std::string)");
        return {};
    }

    std::string contents = m_gamePackage->File()->ReadFileContents(path);
    if (contents.empty())
    {
        Log::Error("Could not read file contents. Filepath: " + path,
            "ToolsSceneLoader::LoadScene(std::string)");
        return {};
    }

    auto rapidDocument = std::make_shared<RapidXMLDocument>();
    if (!rapidDocument->Load(contents))
    {
        Log::Error("Could not load XML for file. Filepath: " + path,
            "ToolsSceneLoader::LoadScene(std::string)");
        return {};
    }

    auto modifiableDocument = std::make_shared<ModifiableDocument>();
    if (!modifiableDocument->Load(rapidDocument))
    {
        Log::Error("Could not transform a stored document into a modifiable document. Filepath: " + path,
            "ToolsSceneLoader::LoadScene(std::string)");
        return {};
    }

    return modifiableDocument;
}
