#include "ControllerInput.h"

#include "ControllerLayout.h"
#include "SuperControllerLayoutFromXML.h"
#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/GamePackage.h"
#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFileSystemDirectory.h"
#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFileSystemFile.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"

using namespace SuperGameInput;

ControllerInput::ControllerInput()
{
    m_controllerLayoutFromXml = std::make_shared<SuperControllerLayoutFromXML>();
}

void ControllerInput::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
    ReloadAllLayouts();
}

void ControllerInput::Update()
{
}

void ControllerInput::ReloadAllLayouts()
{
    if (!m_gamePackage)
    {
        Log::Error("Attempted to reload layouts before setting up.",
            "ControllerInput::ReloadAllLayouts");
        return;
    }

    std::vector<std::string> mappingFiles = 
        m_gamePackage->Directory()->GetFiles(PathToControllerConfigs);
    for (const std::string& filepath : mappingFiles)
    {
        std::string packagePath = Directory::CombinePath(PathToControllerConfigs, filepath);

        std::string fileContents = m_gamePackage->File()->ReadFileContents(packagePath);
        if (!fileContents.empty())
        {
            std::shared_ptr<StoredDocument> newLayoutDocument = std::make_shared<RapidXMLDocument>();
            if (!newLayoutDocument->Load(fileContents))
            {
                Log::Error("Controller layout could not be loaded into a StoredDocument. Path: " + filepath,
                    "ControllerInput::ReloadAllLayouts");
                continue;
            }

            std::string error = {};
            std::shared_ptr<ControllerLayout> newLayout = 
                m_controllerLayoutFromXml->CreateFromDocument(newLayoutDocument, error);
            if (!newLayout)
            {
                Log::Error("Controller layout could not be loaded as a layout. "
                           "Error: "+error+". "
                           "Path: " + filepath,
                    "ControllerInput::ReloadAllLayouts");
                continue;
            }

            m_controllerLayouts.emplace_back(newLayout);
            Log::Info("Added layout: " + filepath);
        }
    }
}
