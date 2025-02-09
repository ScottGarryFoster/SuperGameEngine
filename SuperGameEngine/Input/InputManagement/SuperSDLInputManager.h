#pragma once
#include <unordered_map>

#include "SDLInputManager.h"
#include "Event/KeyboardEvent.h"
#include "Event/KeyboardKeycode.h"
#include "Event/KeySymbol.h"
#include "Event/WindowEvent.h"
#include <SDL.h>

#include "Event/JoyHatEvent.h"

namespace SuperGameInput
{
    class InputManager;

    /// <summary>
    /// Handles and updates user input.
    /// </summary>
    class SuperSDLInputManager : public SDLInputManager
    {
    public:
        virtual ~SuperSDLInputManager() override = default;
        SuperSDLInputManager();

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="gamePackage">Game Package, used to load controller inputs. </param>
        virtual void Setup(const std::shared_ptr<GamePackage>& gamePackage) override;

        /// <summary>
        /// Called once after Tools or Game to reset states of keys.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Called upon every event to handle key and controller changes.
        /// </summary>
        /// <param name="event">Event to inspect. </param>
        virtual void EventUpdate(SDL_Event event) override;

        /// <summary>
        /// Is the given key down.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means currently down. Will fire until up. </returns>
        virtual bool GetKeyDown(const KeyCode& keyCode) const override;

        /// <summary>
        /// Was the key just pressed.
        /// Fires once.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means was just pressed. </returns>
        virtual bool GetKeyPressed(const KeyCode& keyCode) const override;

        /// <summary>
        /// Is the given key just been released.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means key was just released. </returns>
        virtual bool GetKeyUp(const KeyCode& keyCode) const override;

        /// <summary>
        /// Determines if button is down.
        /// Fires every frame the buttons is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button is down this frame. </returns>
        virtual bool ButtonDown(UniversalControllerButton button) const override;

        /// <summary>
        /// Determines if button is pressed.
        /// Fires the first frame button is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button was just pressed. </returns>
        virtual bool ButtonUp(UniversalControllerButton button) const override;

        /// <summary>
        /// Determines if button is was just released.
        /// Fires the first frame a button was released.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">button to test. </param>
        /// <returns>True means button was down and now is released. </returns>
        virtual bool ButtonPressed(UniversalControllerButton button) const override;

    private:
        /// <summary>
        /// Handles and updates user input.
        /// </summary>
        std::shared_ptr<InputManager> m_inputManager;

        /// <summary>
        /// Controllers currently open.
        /// </summary>
        std::unordered_map<int32_t, SDL_GameController*> m_controllers;

        WindowEvent ConvertFromSDL(const SDL_Event& event);
        WindowEventType ConvertFromType(Uint32 type) const;

        KeyboardEvent ConvertKeyboardEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent);

        KeySymbol KeySymbolFromSDLKeySym(SDL_Keysym keysym) const;
        KeyScancode KeyScancodeFromSDLScanCode(SDL_Scancode scanCode) const;
        KeyboardKeycode KeyboardKeycodeFromSDLKeyCode(SDL_Keycode keycode) const;

        ControllerDeviceEvent ConvertControllerDeviceEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent);
        JoystickDeviceEvent ConvertJoystickDeviceEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent);
        JoyButtonEvent ConvertJoyButtonEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent);

        JoyHatEvent ConvertJoyHatEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent);
        JoyAxisEvent ConvertJoyAxisEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent);

        /// <summary>
        /// Updates the instance IDs and open/closed controllers when events occur.
        /// All controllers are opened even those which are never used.
        /// </summary>
        /// <param name="type">Event type. </param>
        /// <param name="controllerDevice">Controller device. </param>
        void UpdateOpenControllers(WindowEventType type, ControllerDeviceEvent& controllerDevice);

        /// <summary>
        /// Opens controller with a Controller instance ID.
        /// </summary>
        /// <param name="instanceID">Instance ID. </param>
        /// <returns>Open controller or nullptr if nothing opened. </returns>
        SDL_GameController* OpenSDLControllerFromInstance(int instanceID);

        /// <summary>
        /// Opens a controller with the index of the controller.
        /// </summary>
        /// <param name="index">Index of the controller. </param>
        /// <returns>Open controller or nullptr if nothing opened. </returns>
        SDL_GameController* OpenSDLControllerFromIndex(int index);

        /// <summary>
        /// Returns a Hat Position from SDL version found in Events.
        /// </summary>
        /// <param name="hatValue">Value provided by SDL2. </param>
        /// <returns>The position of the Hat. </returns>
        HatPosition HatPositionFromValue(Uint8 hatValue);
    };
}
