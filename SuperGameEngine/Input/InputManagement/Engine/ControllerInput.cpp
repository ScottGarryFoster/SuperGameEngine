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
    OnJoyStickButtonUpdate();
}

void ControllerInput::EventUpdate(WindowEvent event)
{
    switch (event.EventType)
    {
        case WindowEventType::SDL_CONTROLLERDEVICEADDED: OnControllerAdded(event); break;
        case WindowEventType::SDL_CONTROLLERDEVICEREMOVED: OnControllerRemoved(event); break;
        case WindowEventType::SDL_JOYBUTTONDOWN:
        case WindowEventType::SDL_JOYBUTTONUP:
            OnJoyStickButtonEvent(event);
            break;
    }

}

bool ControllerInput::ButtonDown(UniversalControllerButton button) const
{
    for (const auto& instanceIT : m_controllerButtonState)
    {
        if (!instanceIT.second.contains(button))
        {
            continue;
        }

        if (EKeyOrButtonState::HasFlag(instanceIT.second.at(button), KeyOrButtonState::Down))
        {
            return true;
        }
    }

    return false;
}

bool ControllerInput::ButtonUp(UniversalControllerButton button) const
{
    for (const auto& instanceIT : m_controllerButtonState)
    {
        if (!instanceIT.second.contains(button))
        {
            continue;
        }

        if (EKeyOrButtonState::HasFlag(instanceIT.second.at(button), KeyOrButtonState::Up))
        {
            return true;
        }
    }

    return false;
}

bool ControllerInput::ButtonPressed(UniversalControllerButton button) const
{
    for (const auto& instanceIT : m_controllerButtonState)
    {
        if (!instanceIT.second.contains(button))
        {
            continue;
        }

        if (EKeyOrButtonState::HasFlag(instanceIT.second.at(button), KeyOrButtonState::Pressed))
        {
            return true;
        }
    }

    return false;
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
        m_controllerButtonState.try_emplace(controllerDevice.ControllerInstanceID, std::unordered_map<UniversalControllerButton, KeyOrButtonState>());
        return true;
    }

    return false;
}

void ControllerInput::OnControllerAdded(const WindowEvent& event)
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

void ControllerInput::OnControllerRemoved(const WindowEvent& event)
{
    m_currentControllers.erase(event.ControllerDevice.ControllerInstanceID);
    m_controllerButtonState.erase(event.ControllerDevice.ControllerInstanceID);
}

void ControllerInput::OnJoyStickButtonEvent(const WindowEvent& event)
{
    UniversalControllerButton mappedButton = GetButtonFromJoyStick(event.JoyButton);
    if (mappedButton == UniversalControllerButton::Unknown)
    {
        return;
    }

    KeyOrButtonState buttonState = m_controllerButtonState.at(event.JoyButton.InstanceID).at(mappedButton);
    if (event.JoyButton.Type == WindowEventType::SDL_JOYBUTTONDOWN)
    {
        if (buttonState == KeyOrButtonState::Unpressed)
        {
            m_controllerButtonState.at(event.JoyButton.InstanceID).at(mappedButton)
                = KeyOrButtonState::Down | KeyOrButtonState::Pressed;
        }
    }
    else if (event.EventType == WindowEventType::SDL_JOYBUTTONUP)
    {
        if (EKeyOrButtonState::HasFlag(buttonState, KeyOrButtonState::Down))
        {
            m_controllerButtonState.at(event.JoyButton.InstanceID).at(mappedButton)
                = KeyOrButtonState::Up;
        }
    }

}

void ControllerInput::OnJoyStickButtonUpdate()
{
    for (auto& instanceIT : m_controllerButtonState)
    {
        for (auto& buttonIT : instanceIT.second)
        {
            if (EKeyOrButtonState::HasFlag(buttonIT.second, KeyOrButtonState::Pressed))
            {
                buttonIT.second = KeyOrButtonState::Down;
            }
            else if (EKeyOrButtonState::HasFlag(buttonIT.second, KeyOrButtonState::Up))
            {
                buttonIT.second = KeyOrButtonState::Unpressed;
            }
        }
    }
}

UniversalControllerButton ControllerInput::GetButtonFromJoyStick(const JoyButtonEvent& joyButton)
{
    if (!m_currentControllers.contains(joyButton.InstanceID))
    {
        Log::Error("Button was pressed on an unknown controller. "
            "InstanceID: " + std::to_string(joyButton.InstanceID),
            "ControllerInput::GetButtonFromJoyStick(const JoyButtonEvent)");
        return UniversalControllerButton::Unknown;
    }

    Controller controllerType = m_currentControllers.at(joyButton.InstanceID);
    if (!m_controllerLayouts.contains(controllerType))
    {
        Log::Error("Button was pressed on a controller without a layout. "
            "InstanceID: " + std::to_string(joyButton.InstanceID),
            "ControllerInput::GetButtonFromJoyStick(const JoyButtonEvent)");
        return UniversalControllerButton::Unknown;
    }

    // We need to understand what button the player has pressed.
    std::shared_ptr<ControllerLayout> layout = m_controllerLayouts.at(controllerType);
    UniversalControllerButton buttonType = UniversalControllerButton::Unknown;
    for (const std::pair<int, UniversalControllerButton>& buttonMapping : layout->SDLToUniversalButton)
    {
        if (buttonMapping.first == joyButton.Button)
        {
            buttonType = buttonMapping.second;
        }
    }

    if (buttonType == UniversalControllerButton::Unknown)
    {
        Log::Error("Unknown button pressed on controller. "
            "Button: " + std::to_string(joyButton.Button) +
            " InstanceID: " + std::to_string(joyButton.InstanceID),
            "ControllerInput::GetButtonFromJoyStick(const JoyButtonEvent)");
        return UniversalControllerButton::Unknown;
    }

    // Now we know the button ensure there are entries for it
    if (!m_controllerButtonState.contains(joyButton.InstanceID))
    {
        m_controllerButtonState.try_emplace(joyButton.InstanceID, std::unordered_map<UniversalControllerButton, KeyOrButtonState>());
    }

    if (!m_controllerButtonState.at(joyButton.InstanceID).contains(buttonType))
    {
        m_controllerButtonState.at(joyButton.InstanceID).try_emplace(buttonType, KeyOrButtonState::Unpressed);
    }

    return buttonType;
}
