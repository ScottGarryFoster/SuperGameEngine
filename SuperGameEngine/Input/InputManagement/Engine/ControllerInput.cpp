#include "ControllerInput.h"

#include "ControllerLayout.h"
#include "SuperControllerLayoutFromXML.h"
#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/GamePackage.h"
#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFileSystemDirectory.h"
#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFileSystemFile.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../Event/WindowEvent.h"

using namespace SuperGameInput;

ControllerInput::ControllerInput()
{
    m_controllerLayoutFromXml = std::make_shared<SuperControllerLayoutFromXML>();
    m_isSetup = false;
}

void ControllerInput::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
    ReloadAllLayouts();

    for (const ControllerDeviceEvent& device : m_pendingDiscovery)
    {
        if (AddController(device))
        {
            Log::Info("Add controller: " + device.Name);
        }
        else
        {
            Log::Error("Could not add controller: " + device.Name + 
                " instance: " +std::to_string(device.ControllerInstanceID),
                "ControllerInput::Setup(std::shared_ptr<GamePackage>)");
        }
    }
    m_pendingDiscovery.clear();

    m_isSetup = true;
}

void ControllerInput::Update()
{
}

void ControllerInput::EventUpdate(WindowEvent event)
{
    if (event.EventType == WindowEventType::SDL_CONTROLLERDEVICEADDED)
    {
        if (m_isSetup)
        {
            if (!AddController(event.ControllerDevice))
            {
                Log::Error("Could not add controller: " + event.ControllerDevice.Name +
                    " instance: " + std::to_string(event.ControllerDevice.ControllerInstanceID),
                    "ControllerInput::Setup(std::shared_ptr<GamePackage>)");
            }
        }
        else
        {
            m_pendingDiscovery.emplace_back(event.ControllerDevice);
        }
    }
    else if (event.EventType == WindowEventType::SDL_CONTROLLERDEVICEREMOVED)
    {
        m_currentControllers.erase(event.ControllerDevice.ControllerInstanceID);
    }
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

            m_controllerLayouts.try_emplace(newLayout->Controller, newLayout);
            Log::Info("Added layout: " + filepath);
        }
    }
}

bool ControllerInput::AddController(const ControllerDeviceEvent& controllerDevice)
{
    for (std::pair<Controller, std::shared_ptr<ControllerLayout>> layout : m_controllerLayouts)
    {
        if (controllerDevice.Name != layout.second->Name)
        {
            continue;
        }

        if (controllerDevice.Axes != layout.second->Axis)
        {
            continue;
        }

        if (controllerDevice.Buttons != layout.second->Buttons)
        {
            continue;
        }

        m_currentControllers.try_emplace(controllerDevice.ControllerInstanceID, layout.first);
        return true;
    }

    return false;
}
