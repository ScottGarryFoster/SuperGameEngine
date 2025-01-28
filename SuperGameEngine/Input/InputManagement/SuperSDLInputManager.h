#pragma once
#include "SDLInputManager.h"
#include "Event/KeyboardEvent.h"
#include "Event/KeyboardKeycode.h"
#include "Event/KeySymbol.h"
#include "Event/WindowEvent.h"

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

    private:
        /// <summary>
        /// Handles and updates user input.
        /// </summary>
        std::shared_ptr<InputManager> m_inputManager;

        WindowEvent ConvertFromSDL(const SDL_Event& event);
        WindowEventType ConvertFromType(Uint32 type) const;

        KeyboardEvent ConvertKeyboardEventFromSDL(const SDL_Event& event);

        KeySymbol KeySymbolFromSDLKeySym(SDL_Keysym keysym) const;
        KeyScancode KeyScancodeFromSDLScanCode(SDL_Scancode scanCode) const;
        KeyboardKeycode KeyboardKeycodeFromSDLKeyCode(SDL_Keycode keycode) const;
    };
}
