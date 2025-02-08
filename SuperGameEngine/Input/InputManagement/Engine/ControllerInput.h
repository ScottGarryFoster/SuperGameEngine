#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "Controller.h"
#include "KeyOrButtonState.h"
#include "UniversalControllerButton.h"

namespace SuperGameInput
{
    struct JoyButtonEvent;
    struct ControllerDeviceEvent;
    class ControllerLayoutFromXML;
    class ControllerLayout;
}

namespace FatedQuestLibraries
{
    class GamePackage;
}

using namespace FatedQuestLibraries;

namespace SuperGameInput
{
    struct WindowEvent;

    /// <summary>
    /// Handles controller Input.
    /// </summary>
    class ControllerInput
    {
    public:
        ControllerInput();
        virtual ~ControllerInput() = default;

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="gamePackage">Game Package, used to load controller inputs. </param>
        virtual void Setup(const std::shared_ptr<GamePackage>& gamePackage);

        /// <summary>
        /// Called once after Tools or Game to reset states of keys.
        /// </summary>
        virtual void Update();

        /// <summary>
        /// Called upon every event to handle key and controller changes.
        /// </summary>
        /// <param name="event">Event to inspect. </param>
        virtual void EventUpdate(WindowEvent event);

        /// <summary>
        /// Determines if button is down.
        /// Fires every frame the buttons is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button is down this frame. </returns>
        bool ButtonDown(UniversalControllerButton button) const;

        /// <summary>
        /// Determines if button is pressed.
        /// Fires the first frame button is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button was just pressed. </returns>
        bool ButtonUp(UniversalControllerButton button) const;

        /// <summary>
        /// Determines if button is was just released.
        /// Fires the first frame a button was released.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">button to test. </param>
        /// <returns>True means button was down and now is released. </returns>
        bool ButtonPressed(UniversalControllerButton button) const;

        /// <summary>
        /// Gets the values on the given Axis.
        /// This is a value -32767 to 32767 with 0 in the middle.
        /// </summary>
        /// <param name="axis">Axis to get the value of. </param>
        /// <returns>Axix value. </returns>
        //int AxisValue(UniversalControllerAxis axis) const;

        /// <summary>
        /// Gets the controller plugged in.
        /// Will get the first controller found which is not 'unknown'.
        /// The first not 'Unknown' controller is the one which is used
        /// for input for the Buttons.
        /// </summary>
        /// <returns>Gets a Valid controller plugged in or 'Unknown' if none found (or recognised). </returns>
        //Controller GetCurrentController() const;

    private:
        /// <summary>
        /// Where to find the controller configuration files.
        /// </summary>
        inline static const std::string PathToControllerConfigs = "Engine\\Input\\ControllerMappings";

        /// <summary>
        /// True means is setup.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        std::shared_ptr<GamePackage> m_gamePackage;

        /// <summary>
        /// All controller layouts. The layouts are the translation from SDL.
        /// </summary>
        std::unordered_map<Controller, std::shared_ptr<ControllerLayout>> m_controllerLayouts;

        /// <summary>
        /// Creates a Controller Layout from XML Format.
        /// </summary>
        std::shared_ptr<ControllerLayoutFromXML> m_controllerLayoutFromXml;

        /// <summary>
        /// Controllers found at application launch before we were setup.
        /// Kept in here until we do setup then removed.
        /// </summary>
        std::vector<ControllerDeviceEvent> m_pendingDiscovery;

        /// <summary>
        /// All controllers by instanceID and Controller.
        /// </summary>
        std::unordered_map<int32_t, Controller> m_currentControllers;

        /// <summary>
        /// The state of buttons on all controllers.
        /// </summary>
        std::unordered_map<int32_t, std::unordered_map<UniversalControllerButton, KeyOrButtonState>> m_controllerButtonState;

        /// <summary>
        /// Loads all layouts into memory from file.
        /// </summary>
        void ReloadAllLayouts();

        /// <summary>
        /// Adds a new controller device.
        /// </summary>
        /// <param name="controllerDevice">New controller to add. </param>
        /// <returns>True means this is a recognised controller. </returns>
        bool AddController(const ControllerDeviceEvent& controllerDevice);

        /// <summary>
        /// Performs tasks based on a new controller added.
        /// </summary>
        /// <param name="event">Event upon being added. </param>
        void OnControllerAdded(const WindowEvent& event);

        /// <summary>
        /// Performs tasks based on a controller being removed.
        /// </summary>
        /// <param name="event">Event to process. </param>
        void OnControllerRemoved(const WindowEvent& event);

        /// <summary>
        /// Occurs on Joystick Button Down or Up.
        /// </summary>
        /// <param name="event">Event to process. </param>
        void OnJoyStickButtonEvent(const WindowEvent& event);

        /// <summary>
        /// Occurs on Update to update the state of button presses.
        /// </summary>
        void OnJoyStickButtonUpdate();

        /// <summary>
        /// Returns the mapped button from the information in a JoyButton Event.
        /// Note when referring to 'Mapped' this refers to the mapping to Universal Buttons not
        /// a player re-mapping.
        /// </summary>
        /// <param name="joystickDeviceEvent">JoyButton event. </param>
        /// <returns>The mapped button or Unknown if there is none. </returns>
        UniversalControllerButton GetButtonFromJoyStick(const JoyButtonEvent& joystickDeviceEvent);
    };
}
