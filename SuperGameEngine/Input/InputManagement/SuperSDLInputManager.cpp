#include "SuperSDLInputManager.h"
#include <SDL.h>
#include <SDL_joystick.h>

#include "SuperInputManager.h"
#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameInput;

SuperSDLInputManager::SuperSDLInputManager()
{
    m_inputManager = std::make_shared<SuperInputManager>();
}

void SuperSDLInputManager::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_inputManager->Setup(gamePackage);
}

void SuperSDLInputManager::Update()
{
    m_inputManager->Update();
}

void SuperSDLInputManager::EventUpdate(SDL_Event e)
{
    m_inputManager->EventUpdate(ConvertFromSDL(e));
}

bool SuperSDLInputManager::GetKeyDown(const KeyCode& keyCode) const
{
    return m_inputManager->GetKeyDown(keyCode);
}

bool SuperSDLInputManager::GetKeyPressed(const KeyCode& keyCode) const
{
    return m_inputManager->GetKeyPressed(keyCode);
}

bool SuperSDLInputManager::GetKeyUp(const KeyCode& keyCode) const
{
    return m_inputManager->GetKeyUp(keyCode);
}

bool SuperSDLInputManager::ButtonDown(UniversalControllerButton button) const
{
    return m_inputManager->ButtonDown(button);
}

bool SuperSDLInputManager::ButtonUp(UniversalControllerButton button) const
{
    return m_inputManager->ButtonUp(button);
}

bool SuperSDLInputManager::ButtonPressed(UniversalControllerButton button) const
{
    return m_inputManager->ButtonPressed(button);
}

int SuperSDLInputManager::AxisValue(UniversalControllerAxis axis) const
{
    return m_inputManager->AxisValue(axis);
}

float SuperSDLInputManager::AxisValueNormalised(UniversalControllerAxis axis) const
{
    return m_inputManager->AxisValueNormalised(axis);
}

MouseState SuperSDLInputManager::GetMouseState() const
{
    return m_inputManager->GetMouseState();
}

WindowEvent SuperSDLInputManager::ConvertFromSDL(const SDL_Event& event)
{
    auto windowEvent = WindowEvent();
    windowEvent.EventType = ConvertFromType(event.type);
    ConvertKeyboardEventFromSDL(event, windowEvent);

    ConvertJoystickDeviceEventFromSDL(event, windowEvent);
    ConvertControllerDeviceEventFromSDL(event, windowEvent);
    UpdateOpenControllers(windowEvent.EventType, windowEvent.ControllerDevice);
    
    ConvertJoyButtonEventFromSDL(event, windowEvent);
    ConvertJoyHatEventFromSDL(event, windowEvent);
    ConvertJoyAxisEventFromSDL(event, windowEvent);

    ConvertMouseButtonEventFromSDL(event, windowEvent);
    return windowEvent;
}

WindowEventType SuperSDLInputManager::ConvertFromType(Uint32 type) const
{
    switch (type)
    {
    case SDL_FIRSTEVENT: return WindowEventType::SDL_FIRSTEVENT;
    case SDL_QUIT: return WindowEventType::SDL_QUIT;
    case SDL_APP_TERMINATING: return WindowEventType::SDL_APP_TERMINATING;
    case SDL_APP_LOWMEMORY: return WindowEventType::SDL_APP_LOWMEMORY;
    case SDL_APP_WILLENTERBACKGROUND: return WindowEventType::SDL_APP_WILLENTERBACKGROUND;
    case SDL_APP_DIDENTERBACKGROUND: return WindowEventType::SDL_APP_DIDENTERBACKGROUND;
    case SDL_APP_WILLENTERFOREGROUND: return WindowEventType::SDL_APP_WILLENTERFOREGROUND;
    case SDL_APP_DIDENTERFOREGROUND: return WindowEventType::SDL_APP_DIDENTERFOREGROUND;
    case SDL_LOCALECHANGED: return WindowEventType::SDL_LOCALECHANGED;
    case SDL_DISPLAYEVENT: return WindowEventType::SDL_DISPLAYEVENT;
    case SDL_WINDOWEVENT: return WindowEventType::SDL_WINDOWEVENT;
    case SDL_SYSWMEVENT: return WindowEventType::SDL_SYSWMEVENT;
    case SDL_KEYDOWN: return WindowEventType::SDL_KEYDOWN;
    case SDL_KEYUP: return WindowEventType::SDL_KEYUP;
    case SDL_TEXTEDITING: return WindowEventType::SDL_TEXTEDITING;
    case SDL_TEXTINPUT: return WindowEventType::SDL_TEXTINPUT;
    case SDL_KEYMAPCHANGED: return WindowEventType::SDL_KEYMAPCHANGED;
    case SDL_TEXTEDITING_EXT: return WindowEventType::SDL_TEXTEDITING_EXT;
    case SDL_MOUSEMOTION: return WindowEventType::SDL_MOUSEMOTION;
    case SDL_MOUSEBUTTONDOWN: return WindowEventType::SDL_MOUSEBUTTONDOWN;
    case SDL_MOUSEBUTTONUP: return WindowEventType::SDL_MOUSEBUTTONUP;
    case SDL_MOUSEWHEEL: return WindowEventType::SDL_MOUSEWHEEL;
    case SDL_JOYAXISMOTION: return WindowEventType::SDL_JOYAXISMOTION;
    case SDL_JOYBALLMOTION: return WindowEventType::SDL_JOYBALLMOTION;
    case SDL_JOYHATMOTION: return WindowEventType::SDL_JOYHATMOTION;
    case SDL_JOYBUTTONDOWN: return WindowEventType::SDL_JOYBUTTONDOWN;
    case SDL_JOYBUTTONUP: return WindowEventType::SDL_JOYBUTTONUP;
    case SDL_JOYDEVICEADDED: return WindowEventType::SDL_JOYDEVICEADDED;
    case SDL_JOYDEVICEREMOVED: return WindowEventType::SDL_JOYDEVICEREMOVED;
    case SDL_JOYBATTERYUPDATED: return WindowEventType::SDL_JOYBATTERYUPDATED;
    case SDL_CONTROLLERAXISMOTION: return WindowEventType::SDL_CONTROLLERAXISMOTION;
    case SDL_CONTROLLERBUTTONDOWN: return WindowEventType::SDL_CONTROLLERBUTTONDOWN;
    case SDL_CONTROLLERBUTTONUP: return WindowEventType::SDL_CONTROLLERBUTTONUP;
    case SDL_CONTROLLERDEVICEADDED: return WindowEventType::SDL_CONTROLLERDEVICEADDED;
    case SDL_CONTROLLERDEVICEREMOVED: return WindowEventType::SDL_CONTROLLERDEVICEREMOVED;
    case SDL_CONTROLLERDEVICEREMAPPED: return WindowEventType::SDL_CONTROLLERDEVICEREMAPPED;
    case SDL_CONTROLLERTOUCHPADDOWN: return WindowEventType::SDL_CONTROLLERTOUCHPADDOWN;
    case SDL_CONTROLLERTOUCHPADMOTION: return WindowEventType::SDL_CONTROLLERTOUCHPADMOTION;
    case SDL_CONTROLLERTOUCHPADUP: return WindowEventType::SDL_CONTROLLERTOUCHPADUP;
    case SDL_CONTROLLERSENSORUPDATE: return WindowEventType::SDL_CONTROLLERSENSORUPDATE;
    case SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3: return WindowEventType::SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3;
    case SDL_CONTROLLERSTEAMHANDLEUPDATED: return WindowEventType::SDL_CONTROLLERSTEAMHANDLEUPDATED;
    case SDL_FINGERDOWN: return WindowEventType::SDL_FINGERDOWN;
    case SDL_FINGERUP: return WindowEventType::SDL_FINGERUP;
    case SDL_FINGERMOTION: return WindowEventType::SDL_FINGERMOTION;
    case SDL_DOLLARGESTURE: return WindowEventType::SDL_DOLLARGESTURE;
    case SDL_DOLLARRECORD: return WindowEventType::SDL_DOLLARRECORD;
    case SDL_MULTIGESTURE: return WindowEventType::SDL_MULTIGESTURE;
    case SDL_CLIPBOARDUPDATE: return WindowEventType::SDL_CLIPBOARDUPDATE;
    case SDL_DROPFILE: return WindowEventType::SDL_DROPFILE;
    case SDL_DROPTEXT: return WindowEventType::SDL_DROPTEXT;
    case SDL_DROPBEGIN: return WindowEventType::SDL_DROPBEGIN;
    case SDL_DROPCOMPLETE: return WindowEventType::SDL_DROPCOMPLETE;
    case SDL_AUDIODEVICEADDED: return WindowEventType::SDL_AUDIODEVICEADDED;
    case SDL_AUDIODEVICEREMOVED: return WindowEventType::SDL_AUDIODEVICEREMOVED;
    case SDL_SENSORUPDATE: return WindowEventType::SDL_SENSORUPDATE;
    case SDL_RENDER_TARGETS_RESET: return WindowEventType::SDL_RENDER_TARGETS_RESET;
    case SDL_RENDER_DEVICE_RESET: return WindowEventType::SDL_RENDER_DEVICE_RESET;
    case SDL_USEREVENT: return WindowEventType::SDL_USEREVENT;
    case SDL_LASTEVENT: return WindowEventType::SDL_LASTEVENT;
    default:
        Log::Error("SDL Event occured which was not found in WindowEventType. Add it. " + std::to_string(type),
            "SuperSDLInputManager::ConvertFromType(Uint32)");
        return WindowEventType::Unknown;
    }
}

KeyboardEvent SuperSDLInputManager::ConvertKeyboardEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    windowEvent.Keyboard.Key = KeySymbolFromSDLKeySym(event.key.keysym);
    return windowEvent.Keyboard;
}

KeySymbol SuperSDLInputManager::KeySymbolFromSDLKeySym(SDL_Keysym keysym) const
{
    auto keySymbol = KeySymbol();
    keySymbol.ScanCode = keysym.scancode == SDL_SCANCODE_UNKNOWN ? KeyScancode::Unknown : KeyScancodeFromSDLScanCode(keysym.scancode);
    keySymbol.Keycode = keysym.sym == SDLK_UNKNOWN ? KeyboardKeycode::Unknown : KeyboardKeycodeFromSDLKeyCode(keysym.sym);
    return keySymbol;
}

KeyScancode SuperSDLInputManager::KeyScancodeFromSDLScanCode(SDL_Scancode scanCode) const
{
    switch (scanCode)
    {
        case SDL_SCANCODE_UNKNOWN: return KeyScancode::Unknown;
        case SDL_SCANCODE_A: return KeyScancode::SDL_SCANCODE_A;
        case SDL_SCANCODE_B: return KeyScancode::SDL_SCANCODE_B;
        case SDL_SCANCODE_C: return KeyScancode::SDL_SCANCODE_C;
        case SDL_SCANCODE_D: return KeyScancode::SDL_SCANCODE_D;
        case SDL_SCANCODE_E: return KeyScancode::SDL_SCANCODE_E;
        case SDL_SCANCODE_F: return KeyScancode::SDL_SCANCODE_F;
        case SDL_SCANCODE_G: return KeyScancode::SDL_SCANCODE_G;
        case SDL_SCANCODE_H: return KeyScancode::SDL_SCANCODE_H;
        case SDL_SCANCODE_I: return KeyScancode::SDL_SCANCODE_I;
        case SDL_SCANCODE_J: return KeyScancode::SDL_SCANCODE_J;
        case SDL_SCANCODE_K: return KeyScancode::SDL_SCANCODE_K;
        case SDL_SCANCODE_L: return KeyScancode::SDL_SCANCODE_L;
        case SDL_SCANCODE_M: return KeyScancode::SDL_SCANCODE_M;
        case SDL_SCANCODE_N: return KeyScancode::SDL_SCANCODE_N;
        case SDL_SCANCODE_O: return KeyScancode::SDL_SCANCODE_O;
        case SDL_SCANCODE_P: return KeyScancode::SDL_SCANCODE_P;
        case SDL_SCANCODE_Q: return KeyScancode::SDL_SCANCODE_Q;
        case SDL_SCANCODE_R: return KeyScancode::SDL_SCANCODE_R;
        case SDL_SCANCODE_S: return KeyScancode::SDL_SCANCODE_S;
        case SDL_SCANCODE_T: return KeyScancode::SDL_SCANCODE_T;
        case SDL_SCANCODE_U: return KeyScancode::SDL_SCANCODE_U;
        case SDL_SCANCODE_V: return KeyScancode::SDL_SCANCODE_V;
        case SDL_SCANCODE_W: return KeyScancode::SDL_SCANCODE_W;
        case SDL_SCANCODE_X: return KeyScancode::SDL_SCANCODE_X;
        case SDL_SCANCODE_Y: return KeyScancode::SDL_SCANCODE_Y;
        case SDL_SCANCODE_Z: return KeyScancode::SDL_SCANCODE_Z;
        case SDL_SCANCODE_1: return KeyScancode::SDL_SCANCODE_1;
        case SDL_SCANCODE_2: return KeyScancode::SDL_SCANCODE_2;
        case SDL_SCANCODE_3: return KeyScancode::SDL_SCANCODE_3;
        case SDL_SCANCODE_4: return KeyScancode::SDL_SCANCODE_4;
        case SDL_SCANCODE_5: return KeyScancode::SDL_SCANCODE_5;
        case SDL_SCANCODE_6: return KeyScancode::SDL_SCANCODE_6;
        case SDL_SCANCODE_7: return KeyScancode::SDL_SCANCODE_7;
        case SDL_SCANCODE_8: return KeyScancode::SDL_SCANCODE_8;
        case SDL_SCANCODE_9: return KeyScancode::SDL_SCANCODE_9;
        case SDL_SCANCODE_0: return KeyScancode::SDL_SCANCODE_0;
        case SDL_SCANCODE_RETURN: return KeyScancode::SDL_SCANCODE_RETURN;
        case SDL_SCANCODE_ESCAPE: return KeyScancode::SDL_SCANCODE_ESCAPE;
        case SDL_SCANCODE_BACKSPACE: return KeyScancode::SDL_SCANCODE_BACKSPACE;
        case SDL_SCANCODE_TAB: return KeyScancode::SDL_SCANCODE_TAB;
        case SDL_SCANCODE_SPACE: return KeyScancode::SDL_SCANCODE_SPACE;
        case SDL_SCANCODE_MINUS: return KeyScancode::SDL_SCANCODE_MINUS;
        case SDL_SCANCODE_EQUALS: return KeyScancode::SDL_SCANCODE_EQUALS;
        case SDL_SCANCODE_LEFTBRACKET: return KeyScancode::SDL_SCANCODE_LEFTBRACKET;
        case SDL_SCANCODE_RIGHTBRACKET: return KeyScancode::SDL_SCANCODE_RIGHTBRACKET;
        case SDL_SCANCODE_BACKSLASH: return KeyScancode::SDL_SCANCODE_BACKSLASH;
        case SDL_SCANCODE_NONUSHASH: return KeyScancode::SDL_SCANCODE_NONUSHASH;
        case SDL_SCANCODE_SEMICOLON: return KeyScancode::SDL_SCANCODE_SEMICOLON;
        case SDL_SCANCODE_APOSTROPHE: return KeyScancode::SDL_SCANCODE_APOSTROPHE;
        case SDL_SCANCODE_GRAVE: return KeyScancode::SDL_SCANCODE_GRAVE;
        case SDL_SCANCODE_COMMA: return KeyScancode::SDL_SCANCODE_COMMA;
        case SDL_SCANCODE_PERIOD: return KeyScancode::SDL_SCANCODE_PERIOD;
        case SDL_SCANCODE_SLASH: return KeyScancode::SDL_SCANCODE_SLASH;
        case SDL_SCANCODE_CAPSLOCK: return KeyScancode::SDL_SCANCODE_CAPSLOCK;
        case SDL_SCANCODE_F1: return KeyScancode::SDL_SCANCODE_F1;
        case SDL_SCANCODE_F2: return KeyScancode::SDL_SCANCODE_F2;
        case SDL_SCANCODE_F3: return KeyScancode::SDL_SCANCODE_F3;
        case SDL_SCANCODE_F4: return KeyScancode::SDL_SCANCODE_F4;
        case SDL_SCANCODE_F5: return KeyScancode::SDL_SCANCODE_F5;
        case SDL_SCANCODE_F6: return KeyScancode::SDL_SCANCODE_F6;
        case SDL_SCANCODE_F7: return KeyScancode::SDL_SCANCODE_F7;
        case SDL_SCANCODE_F8: return KeyScancode::SDL_SCANCODE_F8;
        case SDL_SCANCODE_F9: return KeyScancode::SDL_SCANCODE_F9;
        case SDL_SCANCODE_F10: return KeyScancode::SDL_SCANCODE_F10;
        case SDL_SCANCODE_F11: return KeyScancode::SDL_SCANCODE_F11;
        case SDL_SCANCODE_F12: return KeyScancode::SDL_SCANCODE_F12;
        case SDL_SCANCODE_PRINTSCREEN: return KeyScancode::SDL_SCANCODE_PRINTSCREEN;
        case SDL_SCANCODE_SCROLLLOCK: return KeyScancode::SDL_SCANCODE_SCROLLLOCK;
        case SDL_SCANCODE_PAUSE: return KeyScancode::SDL_SCANCODE_PAUSE;
        case SDL_SCANCODE_INSERT: return KeyScancode::SDL_SCANCODE_INSERT;
        case SDL_SCANCODE_HOME: return KeyScancode::SDL_SCANCODE_HOME;
        case SDL_SCANCODE_PAGEUP: return KeyScancode::SDL_SCANCODE_PAGEUP;
        case SDL_SCANCODE_DELETE: return KeyScancode::SDL_SCANCODE_DELETE;
        case SDL_SCANCODE_END: return KeyScancode::SDL_SCANCODE_END;
        case SDL_SCANCODE_PAGEDOWN: return KeyScancode::SDL_SCANCODE_PAGEDOWN;
        case SDL_SCANCODE_RIGHT: return KeyScancode::SDL_SCANCODE_RIGHT;
        case SDL_SCANCODE_LEFT: return KeyScancode::SDL_SCANCODE_LEFT;
        case SDL_SCANCODE_DOWN: return KeyScancode::SDL_SCANCODE_DOWN;
        case SDL_SCANCODE_UP: return KeyScancode::SDL_SCANCODE_UP;
        case SDL_SCANCODE_NUMLOCKCLEAR: return KeyScancode::SDL_SCANCODE_NUMLOCKCLEAR;
        case SDL_SCANCODE_KP_DIVIDE: return KeyScancode::SDL_SCANCODE_KP_DIVIDE;
        case SDL_SCANCODE_KP_MULTIPLY: return KeyScancode::SDL_SCANCODE_KP_MULTIPLY;
        case SDL_SCANCODE_KP_MINUS: return KeyScancode::SDL_SCANCODE_KP_MINUS;
        case SDL_SCANCODE_KP_PLUS: return KeyScancode::SDL_SCANCODE_KP_PLUS;
        case SDL_SCANCODE_KP_ENTER: return KeyScancode::SDL_SCANCODE_KP_ENTER;
        case SDL_SCANCODE_KP_1: return KeyScancode::SDL_SCANCODE_KP_1;
        case SDL_SCANCODE_KP_2: return KeyScancode::SDL_SCANCODE_KP_2;
        case SDL_SCANCODE_KP_3: return KeyScancode::SDL_SCANCODE_KP_3;
        case SDL_SCANCODE_KP_4: return KeyScancode::SDL_SCANCODE_KP_4;
        case SDL_SCANCODE_KP_5: return KeyScancode::SDL_SCANCODE_KP_5;
        case SDL_SCANCODE_KP_6: return KeyScancode::SDL_SCANCODE_KP_6;
        case SDL_SCANCODE_KP_7: return KeyScancode::SDL_SCANCODE_KP_7;
        case SDL_SCANCODE_KP_8: return KeyScancode::SDL_SCANCODE_KP_8;
        case SDL_SCANCODE_KP_9: return KeyScancode::SDL_SCANCODE_KP_9;
        case SDL_SCANCODE_KP_0: return KeyScancode::SDL_SCANCODE_KP_0;
        case SDL_SCANCODE_KP_PERIOD: return KeyScancode::SDL_SCANCODE_KP_PERIOD;
        case SDL_SCANCODE_NONUSBACKSLASH: return KeyScancode::SDL_SCANCODE_NONUSBACKSLASH;
        case SDL_SCANCODE_APPLICATION: return KeyScancode::SDL_SCANCODE_APPLICATION;
        case SDL_SCANCODE_POWER: return KeyScancode::SDL_SCANCODE_POWER;
        case SDL_SCANCODE_KP_EQUALS: return KeyScancode::SDL_SCANCODE_KP_EQUALS;
        case SDL_SCANCODE_F13: return KeyScancode::SDL_SCANCODE_F13;
        case SDL_SCANCODE_F14: return KeyScancode::SDL_SCANCODE_F14;
        case SDL_SCANCODE_F15: return KeyScancode::SDL_SCANCODE_F15;
        case SDL_SCANCODE_F16: return KeyScancode::SDL_SCANCODE_F16;
        case SDL_SCANCODE_F17: return KeyScancode::SDL_SCANCODE_F17;
        case SDL_SCANCODE_F18: return KeyScancode::SDL_SCANCODE_F18;
        case SDL_SCANCODE_F19: return KeyScancode::SDL_SCANCODE_F19;
        case SDL_SCANCODE_F20: return KeyScancode::SDL_SCANCODE_F20;
        case SDL_SCANCODE_F21: return KeyScancode::SDL_SCANCODE_F21;
        case SDL_SCANCODE_F22: return KeyScancode::SDL_SCANCODE_F22;
        case SDL_SCANCODE_F23: return KeyScancode::SDL_SCANCODE_F23;
        case SDL_SCANCODE_F24: return KeyScancode::SDL_SCANCODE_F24;
        case SDL_SCANCODE_EXECUTE: return KeyScancode::SDL_SCANCODE_EXECUTE;
        case SDL_SCANCODE_HELP: return KeyScancode::SDL_SCANCODE_HELP;
        case SDL_SCANCODE_MENU: return KeyScancode::SDL_SCANCODE_MENU;
        case SDL_SCANCODE_SELECT: return KeyScancode::SDL_SCANCODE_SELECT;
        case SDL_SCANCODE_STOP: return KeyScancode::SDL_SCANCODE_STOP;
        case SDL_SCANCODE_AGAIN: return KeyScancode::SDL_SCANCODE_AGAIN;
        case SDL_SCANCODE_UNDO: return KeyScancode::SDL_SCANCODE_UNDO;
        case SDL_SCANCODE_CUT: return KeyScancode::SDL_SCANCODE_CUT;
        case SDL_SCANCODE_COPY: return KeyScancode::SDL_SCANCODE_COPY;
        case SDL_SCANCODE_PASTE: return KeyScancode::SDL_SCANCODE_PASTE;
        case SDL_SCANCODE_FIND: return KeyScancode::SDL_SCANCODE_FIND;
        case SDL_SCANCODE_MUTE: return KeyScancode::SDL_SCANCODE_MUTE;
        case SDL_SCANCODE_VOLUMEUP: return KeyScancode::SDL_SCANCODE_VOLUMEUP;
        case SDL_SCANCODE_VOLUMEDOWN: return KeyScancode::SDL_SCANCODE_VOLUMEDOWN;
        case SDL_SCANCODE_KP_COMMA: return KeyScancode::SDL_SCANCODE_KP_COMMA;
        case SDL_SCANCODE_KP_EQUALSAS400: return KeyScancode::SDL_SCANCODE_KP_EQUALSAS400;
        case SDL_SCANCODE_INTERNATIONAL1: return KeyScancode::SDL_SCANCODE_INTERNATIONAL1;
        case SDL_SCANCODE_INTERNATIONAL2: return KeyScancode::SDL_SCANCODE_INTERNATIONAL2;
        case SDL_SCANCODE_INTERNATIONAL3: return KeyScancode::SDL_SCANCODE_INTERNATIONAL3;
        case SDL_SCANCODE_INTERNATIONAL4: return KeyScancode::SDL_SCANCODE_INTERNATIONAL4;
        case SDL_SCANCODE_INTERNATIONAL5: return KeyScancode::SDL_SCANCODE_INTERNATIONAL5;
        case SDL_SCANCODE_INTERNATIONAL6: return KeyScancode::SDL_SCANCODE_INTERNATIONAL6;
        case SDL_SCANCODE_INTERNATIONAL7: return KeyScancode::SDL_SCANCODE_INTERNATIONAL7;
        case SDL_SCANCODE_INTERNATIONAL8: return KeyScancode::SDL_SCANCODE_INTERNATIONAL8;
        case SDL_SCANCODE_INTERNATIONAL9: return KeyScancode::SDL_SCANCODE_INTERNATIONAL9;
        case SDL_SCANCODE_LANG1: return KeyScancode::SDL_SCANCODE_LANG1;
        case SDL_SCANCODE_LANG2: return KeyScancode::SDL_SCANCODE_LANG2;
        case SDL_SCANCODE_LANG3: return KeyScancode::SDL_SCANCODE_LANG3;
        case SDL_SCANCODE_LANG4: return KeyScancode::SDL_SCANCODE_LANG4;
        case SDL_SCANCODE_LANG5: return KeyScancode::SDL_SCANCODE_LANG5;
        case SDL_SCANCODE_LANG6: return KeyScancode::SDL_SCANCODE_LANG6;
        case SDL_SCANCODE_LANG7: return KeyScancode::SDL_SCANCODE_LANG7;
        case SDL_SCANCODE_LANG8: return KeyScancode::SDL_SCANCODE_LANG8;
        case SDL_SCANCODE_LANG9: return KeyScancode::SDL_SCANCODE_LANG9;
        case SDL_SCANCODE_ALTERASE: return KeyScancode::SDL_SCANCODE_ALTERASE;
        case SDL_SCANCODE_SYSREQ: return KeyScancode::SDL_SCANCODE_SYSREQ;
        case SDL_SCANCODE_CANCEL: return KeyScancode::SDL_SCANCODE_CANCEL;
        case SDL_SCANCODE_CLEAR: return KeyScancode::SDL_SCANCODE_CLEAR;
        case SDL_SCANCODE_PRIOR: return KeyScancode::SDL_SCANCODE_PRIOR;
        case SDL_SCANCODE_RETURN2: return KeyScancode::SDL_SCANCODE_RETURN2;
        case SDL_SCANCODE_SEPARATOR: return KeyScancode::SDL_SCANCODE_SEPARATOR;
        case SDL_SCANCODE_OUT: return KeyScancode::SDL_SCANCODE_OUT;
        case SDL_SCANCODE_OPER: return KeyScancode::SDL_SCANCODE_OPER;
        case SDL_SCANCODE_CLEARAGAIN: return KeyScancode::SDL_SCANCODE_CLEARAGAIN;
        case SDL_SCANCODE_CRSEL: return KeyScancode::SDL_SCANCODE_CRSEL;
        case SDL_SCANCODE_EXSEL: return KeyScancode::SDL_SCANCODE_EXSEL;
        case SDL_SCANCODE_KP_00: return KeyScancode::SDL_SCANCODE_KP_00;
        case SDL_SCANCODE_KP_000: return KeyScancode::SDL_SCANCODE_KP_000;
        case SDL_SCANCODE_THOUSANDSSEPARATOR: return KeyScancode::SDL_SCANCODE_THOUSANDSSEPARATOR;
        case SDL_SCANCODE_DECIMALSEPARATOR: return KeyScancode::SDL_SCANCODE_DECIMALSEPARATOR;
        case SDL_SCANCODE_CURRENCYUNIT: return KeyScancode::SDL_SCANCODE_CURRENCYUNIT;
        case SDL_SCANCODE_CURRENCYSUBUNIT: return KeyScancode::SDL_SCANCODE_CURRENCYSUBUNIT;
        case SDL_SCANCODE_KP_LEFTPAREN: return KeyScancode::SDL_SCANCODE_KP_LEFTPAREN;
        case SDL_SCANCODE_KP_RIGHTPAREN: return KeyScancode::SDL_SCANCODE_KP_RIGHTPAREN;
        case SDL_SCANCODE_KP_LEFTBRACE: return KeyScancode::SDL_SCANCODE_KP_LEFTBRACE;
        case SDL_SCANCODE_KP_RIGHTBRACE: return KeyScancode::SDL_SCANCODE_KP_RIGHTBRACE;
        case SDL_SCANCODE_KP_TAB: return KeyScancode::SDL_SCANCODE_KP_TAB;
        case SDL_SCANCODE_KP_BACKSPACE: return KeyScancode::SDL_SCANCODE_KP_BACKSPACE;
        case SDL_SCANCODE_KP_A: return KeyScancode::SDL_SCANCODE_KP_A;
        case SDL_SCANCODE_KP_B: return KeyScancode::SDL_SCANCODE_KP_B;
        case SDL_SCANCODE_KP_C: return KeyScancode::SDL_SCANCODE_KP_C;
        case SDL_SCANCODE_KP_D: return KeyScancode::SDL_SCANCODE_KP_D;
        case SDL_SCANCODE_KP_E: return KeyScancode::SDL_SCANCODE_KP_E;
        case SDL_SCANCODE_KP_F: return KeyScancode::SDL_SCANCODE_KP_F;
        case SDL_SCANCODE_KP_XOR: return KeyScancode::SDL_SCANCODE_KP_XOR;
        case SDL_SCANCODE_KP_POWER: return KeyScancode::SDL_SCANCODE_KP_POWER;
        case SDL_SCANCODE_KP_PERCENT: return KeyScancode::SDL_SCANCODE_KP_PERCENT;
        case SDL_SCANCODE_KP_LESS: return KeyScancode::SDL_SCANCODE_KP_LESS;
        case SDL_SCANCODE_KP_GREATER: return KeyScancode::SDL_SCANCODE_KP_GREATER;
        case SDL_SCANCODE_KP_AMPERSAND: return KeyScancode::SDL_SCANCODE_KP_AMPERSAND;
        case SDL_SCANCODE_KP_DBLAMPERSAND: return KeyScancode::SDL_SCANCODE_KP_DBLAMPERSAND;
        case SDL_SCANCODE_KP_VERTICALBAR: return KeyScancode::SDL_SCANCODE_KP_VERTICALBAR;
        case SDL_SCANCODE_KP_DBLVERTICALBAR: return KeyScancode::SDL_SCANCODE_KP_DBLVERTICALBAR;
        case SDL_SCANCODE_KP_COLON: return KeyScancode::SDL_SCANCODE_KP_COLON;
        case SDL_SCANCODE_KP_HASH: return KeyScancode::SDL_SCANCODE_KP_HASH;
        case SDL_SCANCODE_KP_SPACE: return KeyScancode::SDL_SCANCODE_KP_SPACE;
        case SDL_SCANCODE_KP_AT: return KeyScancode::SDL_SCANCODE_KP_AT;
        case SDL_SCANCODE_KP_EXCLAM: return KeyScancode::SDL_SCANCODE_KP_EXCLAM;
        case SDL_SCANCODE_KP_MEMSTORE: return KeyScancode::SDL_SCANCODE_KP_MEMSTORE;
        case SDL_SCANCODE_KP_MEMRECALL: return KeyScancode::SDL_SCANCODE_KP_MEMRECALL;
        case SDL_SCANCODE_KP_MEMCLEAR: return KeyScancode::SDL_SCANCODE_KP_MEMCLEAR;
        case SDL_SCANCODE_KP_MEMADD: return KeyScancode::SDL_SCANCODE_KP_MEMADD;
        case SDL_SCANCODE_KP_MEMSUBTRACT: return KeyScancode::SDL_SCANCODE_KP_MEMSUBTRACT;
        case SDL_SCANCODE_KP_MEMMULTIPLY: return KeyScancode::SDL_SCANCODE_KP_MEMMULTIPLY;
        case SDL_SCANCODE_KP_MEMDIVIDE: return KeyScancode::SDL_SCANCODE_KP_MEMDIVIDE;
        case SDL_SCANCODE_KP_PLUSMINUS: return KeyScancode::SDL_SCANCODE_KP_PLUSMINUS;
        case SDL_SCANCODE_KP_CLEAR: return KeyScancode::SDL_SCANCODE_KP_CLEAR;
        case SDL_SCANCODE_KP_CLEARENTRY: return KeyScancode::SDL_SCANCODE_KP_CLEARENTRY;
        case SDL_SCANCODE_KP_BINARY: return KeyScancode::SDL_SCANCODE_KP_BINARY;
        case SDL_SCANCODE_KP_OCTAL: return KeyScancode::SDL_SCANCODE_KP_OCTAL;
        case SDL_SCANCODE_KP_DECIMAL: return KeyScancode::SDL_SCANCODE_KP_DECIMAL;
        case SDL_SCANCODE_KP_HEXADECIMAL: return KeyScancode::SDL_SCANCODE_KP_HEXADECIMAL;
        case SDL_SCANCODE_LCTRL: return KeyScancode::SDL_SCANCODE_LCTRL;
        case SDL_SCANCODE_LSHIFT: return KeyScancode::SDL_SCANCODE_LSHIFT;
        case SDL_SCANCODE_LALT: return KeyScancode::SDL_SCANCODE_LALT;
        case SDL_SCANCODE_LGUI: return KeyScancode::SDL_SCANCODE_LGUI;
        case SDL_SCANCODE_RCTRL: return KeyScancode::SDL_SCANCODE_RCTRL;
        case SDL_SCANCODE_RSHIFT: return KeyScancode::SDL_SCANCODE_RSHIFT;
        case SDL_SCANCODE_RALT: return KeyScancode::SDL_SCANCODE_RALT;
        case SDL_SCANCODE_RGUI: return KeyScancode::SDL_SCANCODE_RGUI;
        case SDL_SCANCODE_MODE: return KeyScancode::SDL_SCANCODE_MODE;
        case SDL_SCANCODE_AUDIONEXT: return KeyScancode::SDL_SCANCODE_AUDIONEXT;
        case SDL_SCANCODE_AUDIOPREV: return KeyScancode::SDL_SCANCODE_AUDIOPREV;
        case SDL_SCANCODE_AUDIOSTOP: return KeyScancode::SDL_SCANCODE_AUDIOSTOP;
        case SDL_SCANCODE_AUDIOPLAY: return KeyScancode::SDL_SCANCODE_AUDIOPLAY;
        case SDL_SCANCODE_AUDIOMUTE: return KeyScancode::SDL_SCANCODE_AUDIOMUTE;
        case SDL_SCANCODE_MEDIASELECT: return KeyScancode::SDL_SCANCODE_MEDIASELECT;
        case SDL_SCANCODE_WWW: return KeyScancode::SDL_SCANCODE_WWW;
        case SDL_SCANCODE_MAIL: return KeyScancode::SDL_SCANCODE_MAIL;
        case SDL_SCANCODE_CALCULATOR: return KeyScancode::SDL_SCANCODE_CALCULATOR;
        case SDL_SCANCODE_COMPUTER: return KeyScancode::SDL_SCANCODE_COMPUTER;
        case SDL_SCANCODE_AC_SEARCH: return KeyScancode::SDL_SCANCODE_AC_SEARCH;
        case SDL_SCANCODE_AC_HOME: return KeyScancode::SDL_SCANCODE_AC_HOME;
        case SDL_SCANCODE_AC_BACK: return KeyScancode::SDL_SCANCODE_AC_BACK;
        case SDL_SCANCODE_AC_FORWARD: return KeyScancode::SDL_SCANCODE_AC_FORWARD;
        case SDL_SCANCODE_AC_STOP: return KeyScancode::SDL_SCANCODE_AC_STOP;
        case SDL_SCANCODE_AC_REFRESH: return KeyScancode::SDL_SCANCODE_AC_REFRESH;
        case SDL_SCANCODE_AC_BOOKMARKS: return KeyScancode::SDL_SCANCODE_AC_BOOKMARKS;
        case SDL_SCANCODE_BRIGHTNESSDOWN: return KeyScancode::SDL_SCANCODE_BRIGHTNESSDOWN;
        case SDL_SCANCODE_BRIGHTNESSUP: return KeyScancode::SDL_SCANCODE_BRIGHTNESSUP;
        case SDL_SCANCODE_DISPLAYSWITCH: return KeyScancode::SDL_SCANCODE_DISPLAYSWITCH;
        case SDL_SCANCODE_KBDILLUMTOGGLE: return KeyScancode::SDL_SCANCODE_KBDILLUMTOGGLE;
        case SDL_SCANCODE_KBDILLUMDOWN: return KeyScancode::SDL_SCANCODE_KBDILLUMDOWN;
        case SDL_SCANCODE_KBDILLUMUP: return KeyScancode::SDL_SCANCODE_KBDILLUMUP;
        case SDL_SCANCODE_EJECT: return KeyScancode::SDL_SCANCODE_EJECT;
        case SDL_SCANCODE_SLEEP: return KeyScancode::SDL_SCANCODE_SLEEP;
        case SDL_SCANCODE_APP1: return KeyScancode::SDL_SCANCODE_APP1;
        case SDL_SCANCODE_APP2: return KeyScancode::SDL_SCANCODE_APP2;
        case SDL_NUM_SCANCODES: return KeyScancode::Unknown;
        default:
            return KeyScancode::Unknown;
    }
}

KeyboardKeycode SuperSDLInputManager::KeyboardKeycodeFromSDLKeyCode(SDL_Keycode keycode) const
{
    switch (keycode)
    {
        case SDLK_UNKNOWN: return KeyboardKeycode::Unknown;
        case SDLK_RETURN: return KeyboardKeycode::SDLK_RETURN;
        case SDLK_ESCAPE: return KeyboardKeycode::SDLK_ESCAPE;
        case SDLK_BACKSPACE: return KeyboardKeycode::SDLK_BACKSPACE;
        case SDLK_TAB: return KeyboardKeycode::SDLK_TAB;
        case SDLK_SPACE: return KeyboardKeycode::SDLK_SPACE;
        case SDLK_EXCLAIM: return KeyboardKeycode::SDLK_EXCLAIM;
        case SDLK_QUOTEDBL: return KeyboardKeycode::SDLK_QUOTEDBL;
        case SDLK_HASH: return KeyboardKeycode::SDLK_HASH;
        case SDLK_PERCENT: return KeyboardKeycode::SDLK_PERCENT;
        case SDLK_DOLLAR: return KeyboardKeycode::SDLK_DOLLAR;
        case SDLK_AMPERSAND: return KeyboardKeycode::SDLK_AMPERSAND;
        case SDLK_QUOTE: return KeyboardKeycode::SDLK_QUOTE;
        case SDLK_LEFTPAREN: return KeyboardKeycode::SDLK_LEFTPAREN;
        case SDLK_RIGHTPAREN: return KeyboardKeycode::SDLK_RIGHTPAREN;
        case SDLK_ASTERISK: return KeyboardKeycode::SDLK_ASTERISK;
        case SDLK_PLUS: return KeyboardKeycode::SDLK_PLUS;
        case SDLK_COMMA: return KeyboardKeycode::SDLK_COMMA;
        case SDLK_MINUS: return KeyboardKeycode::SDLK_MINUS;
        case SDLK_PERIOD: return KeyboardKeycode::SDLK_PERIOD;
        case SDLK_SLASH: return KeyboardKeycode::SDLK_SLASH;
        case SDLK_0: return KeyboardKeycode::SDLK_0;
        case SDLK_1: return KeyboardKeycode::SDLK_1;
        case SDLK_2: return KeyboardKeycode::SDLK_2;
        case SDLK_3: return KeyboardKeycode::SDLK_3;
        case SDLK_4: return KeyboardKeycode::SDLK_4;
        case SDLK_5: return KeyboardKeycode::SDLK_5;
        case SDLK_6: return KeyboardKeycode::SDLK_6;
        case SDLK_7: return KeyboardKeycode::SDLK_7;
        case SDLK_8: return KeyboardKeycode::SDLK_8;
        case SDLK_9: return KeyboardKeycode::SDLK_9;
        case SDLK_COLON: return KeyboardKeycode::SDLK_COLON;
        case SDLK_SEMICOLON: return KeyboardKeycode::SDLK_SEMICOLON;
        case SDLK_LESS: return KeyboardKeycode::SDLK_LESS;
        case SDLK_EQUALS: return KeyboardKeycode::SDLK_EQUALS;
        case SDLK_GREATER: return KeyboardKeycode::SDLK_GREATER;
        case SDLK_QUESTION: return KeyboardKeycode::SDLK_QUESTION;
        case SDLK_AT: return KeyboardKeycode::SDLK_AT;
        case SDLK_LEFTBRACKET: return KeyboardKeycode::SDLK_LEFTBRACKET;
        case SDLK_BACKSLASH: return KeyboardKeycode::SDLK_BACKSLASH;
        case SDLK_RIGHTBRACKET: return KeyboardKeycode::SDLK_RIGHTBRACKET;
        case SDLK_CARET: return KeyboardKeycode::SDLK_CARET;
        case SDLK_UNDERSCORE: return KeyboardKeycode::SDLK_UNDERSCORE;
        case SDLK_BACKQUOTE: return KeyboardKeycode::SDLK_BACKQUOTE;
        case SDLK_a: return KeyboardKeycode::SDLK_a;
        case SDLK_b: return KeyboardKeycode::SDLK_b;
        case SDLK_c: return KeyboardKeycode::SDLK_c;
        case SDLK_d: return KeyboardKeycode::SDLK_d;
        case SDLK_e: return KeyboardKeycode::SDLK_e;
        case SDLK_f: return KeyboardKeycode::SDLK_f;
        case SDLK_g: return KeyboardKeycode::SDLK_g;
        case SDLK_h: return KeyboardKeycode::SDLK_h;
        case SDLK_i: return KeyboardKeycode::SDLK_i;
        case SDLK_j: return KeyboardKeycode::SDLK_j;
        case SDLK_k: return KeyboardKeycode::SDLK_k;
        case SDLK_l: return KeyboardKeycode::SDLK_l;
        case SDLK_m: return KeyboardKeycode::SDLK_m;
        case SDLK_n: return KeyboardKeycode::SDLK_n;
        case SDLK_o: return KeyboardKeycode::SDLK_o;
        case SDLK_p: return KeyboardKeycode::SDLK_p;
        case SDLK_q: return KeyboardKeycode::SDLK_q;
        case SDLK_r: return KeyboardKeycode::SDLK_r;
        case SDLK_s: return KeyboardKeycode::SDLK_s;
        case SDLK_t: return KeyboardKeycode::SDLK_t;
        case SDLK_u: return KeyboardKeycode::SDLK_u;
        case SDLK_v: return KeyboardKeycode::SDLK_v;
        case SDLK_w: return KeyboardKeycode::SDLK_w;
        case SDLK_x: return KeyboardKeycode::SDLK_x;
        case SDLK_y: return KeyboardKeycode::SDLK_y;
        case SDLK_z: return KeyboardKeycode::SDLK_z;
        case SDLK_CAPSLOCK: return KeyboardKeycode::SDLK_CAPSLOCK;
        case SDLK_F1: return KeyboardKeycode::SDLK_F1;
        case SDLK_F2: return KeyboardKeycode::SDLK_F2;
        case SDLK_F3: return KeyboardKeycode::SDLK_F3;
        case SDLK_F4: return KeyboardKeycode::SDLK_F4;
        case SDLK_F5: return KeyboardKeycode::SDLK_F5;
        case SDLK_F6: return KeyboardKeycode::SDLK_F6;
        case SDLK_F7: return KeyboardKeycode::SDLK_F7;
        case SDLK_F8: return KeyboardKeycode::SDLK_F8;
        case SDLK_F9: return KeyboardKeycode::SDLK_F9;
        case SDLK_F10: return KeyboardKeycode::SDLK_F10;
        case SDLK_F11: return KeyboardKeycode::SDLK_F11;
        case SDLK_F12: return KeyboardKeycode::SDLK_F12;
        case SDLK_PRINTSCREEN: return KeyboardKeycode::SDLK_PRINTSCREEN;
        case SDLK_SCROLLLOCK: return KeyboardKeycode::SDLK_SCROLLLOCK;
        case SDLK_PAUSE: return KeyboardKeycode::SDLK_PAUSE;
        case SDLK_INSERT: return KeyboardKeycode::SDLK_INSERT;
        case SDLK_HOME: return KeyboardKeycode::SDLK_HOME;
        case SDLK_PAGEUP: return KeyboardKeycode::SDLK_PAGEUP;
        case SDLK_DELETE: return KeyboardKeycode::SDLK_DELETE;
        case SDLK_END: return KeyboardKeycode::SDLK_END;
        case SDLK_PAGEDOWN: return KeyboardKeycode::SDLK_PAGEDOWN;
        case SDLK_RIGHT: return KeyboardKeycode::SDLK_RIGHT;
        case SDLK_LEFT: return KeyboardKeycode::SDLK_LEFT;
        case SDLK_DOWN: return KeyboardKeycode::SDLK_DOWN;
        case SDLK_UP: return KeyboardKeycode::SDLK_UP;
        case SDLK_NUMLOCKCLEAR: return KeyboardKeycode::SDLK_NUMLOCKCLEAR;
        case SDLK_KP_DIVIDE: return KeyboardKeycode::SDLK_KP_DIVIDE;
        case SDLK_KP_MULTIPLY: return KeyboardKeycode::SDLK_KP_MULTIPLY;
        case SDLK_KP_MINUS: return KeyboardKeycode::SDLK_KP_MINUS;
        case SDLK_KP_PLUS: return KeyboardKeycode::SDLK_KP_PLUS;
        case SDLK_KP_ENTER: return KeyboardKeycode::SDLK_KP_ENTER;
        case SDLK_KP_1: return KeyboardKeycode::SDLK_KP_1;
        case SDLK_KP_2: return KeyboardKeycode::SDLK_KP_2;
        case SDLK_KP_3: return KeyboardKeycode::SDLK_KP_3;
        case SDLK_KP_4: return KeyboardKeycode::SDLK_KP_4;
        case SDLK_KP_5: return KeyboardKeycode::SDLK_KP_5;
        case SDLK_KP_6: return KeyboardKeycode::SDLK_KP_6;
        case SDLK_KP_7: return KeyboardKeycode::SDLK_KP_7;
        case SDLK_KP_8: return KeyboardKeycode::SDLK_KP_8;
        case SDLK_KP_9: return KeyboardKeycode::SDLK_KP_9;
        case SDLK_KP_0: return KeyboardKeycode::SDLK_KP_0;
        case SDLK_KP_PERIOD: return KeyboardKeycode::SDLK_KP_PERIOD;
        case SDLK_APPLICATION: return KeyboardKeycode::SDLK_APPLICATION;
        case SDLK_POWER: return KeyboardKeycode::SDLK_POWER;
        case SDLK_KP_EQUALS: return KeyboardKeycode::SDLK_KP_EQUALS;
        case SDLK_F13: return KeyboardKeycode::SDLK_F13;
        case SDLK_F14: return KeyboardKeycode::SDLK_F14;
        case SDLK_F15: return KeyboardKeycode::SDLK_F15;
        case SDLK_F16: return KeyboardKeycode::SDLK_F16;
        case SDLK_F17: return KeyboardKeycode::SDLK_F17;
        case SDLK_F18: return KeyboardKeycode::SDLK_F18;
        case SDLK_F19: return KeyboardKeycode::SDLK_F19;
        case SDLK_F20: return KeyboardKeycode::SDLK_F20;
        case SDLK_F21: return KeyboardKeycode::SDLK_F21;
        case SDLK_F22: return KeyboardKeycode::SDLK_F22;
        case SDLK_F23: return KeyboardKeycode::SDLK_F23;
        case SDLK_F24: return KeyboardKeycode::SDLK_F24;
        case SDLK_EXECUTE: return KeyboardKeycode::SDLK_EXECUTE;
        case SDLK_HELP: return KeyboardKeycode::SDLK_HELP;
        case SDLK_MENU: return KeyboardKeycode::SDLK_MENU;
        case SDLK_SELECT: return KeyboardKeycode::SDLK_SELECT;
        case SDLK_STOP: return KeyboardKeycode::SDLK_STOP;
        case SDLK_AGAIN: return KeyboardKeycode::SDLK_AGAIN;
        case SDLK_UNDO: return KeyboardKeycode::SDLK_UNDO;
        case SDLK_CUT: return KeyboardKeycode::SDLK_CUT;
        case SDLK_COPY: return KeyboardKeycode::SDLK_COPY;
        case SDLK_PASTE: return KeyboardKeycode::SDLK_PASTE;
        case SDLK_FIND: return KeyboardKeycode::SDLK_FIND;
        case SDLK_MUTE: return KeyboardKeycode::SDLK_MUTE;
        case SDLK_VOLUMEUP: return KeyboardKeycode::SDLK_VOLUMEUP;
        case SDLK_VOLUMEDOWN: return KeyboardKeycode::SDLK_VOLUMEDOWN;
        case SDLK_KP_COMMA: return KeyboardKeycode::SDLK_KP_COMMA;
        case SDLK_KP_EQUALSAS400: return KeyboardKeycode::SDLK_KP_EQUALSAS400;
        case SDLK_ALTERASE: return KeyboardKeycode::SDLK_ALTERASE;
        case SDLK_SYSREQ: return KeyboardKeycode::SDLK_SYSREQ;
        case SDLK_CANCEL: return KeyboardKeycode::SDLK_CANCEL;
        case SDLK_CLEAR: return KeyboardKeycode::SDLK_CLEAR;
        case SDLK_PRIOR: return KeyboardKeycode::SDLK_PRIOR;
        case SDLK_RETURN2: return KeyboardKeycode::SDLK_RETURN2;
        case SDLK_SEPARATOR: return KeyboardKeycode::SDLK_SEPARATOR;
        case SDLK_OUT: return KeyboardKeycode::SDLK_OUT;
        case SDLK_OPER: return KeyboardKeycode::SDLK_OPER;
        case SDLK_CLEARAGAIN: return KeyboardKeycode::SDLK_CLEARAGAIN;
        case SDLK_CRSEL: return KeyboardKeycode::SDLK_CRSEL;
        case SDLK_EXSEL: return KeyboardKeycode::SDLK_EXSEL;
        case SDLK_KP_00: return KeyboardKeycode::SDLK_KP_00;
        case SDLK_KP_000: return KeyboardKeycode::SDLK_KP_000;
        case SDLK_THOUSANDSSEPARATOR: return KeyboardKeycode::SDLK_THOUSANDSSEPARATOR;
        case SDLK_DECIMALSEPARATOR: return KeyboardKeycode::SDLK_DECIMALSEPARATOR;
        case SDLK_CURRENCYUNIT: return KeyboardKeycode::SDLK_CURRENCYUNIT;
        case SDLK_CURRENCYSUBUNIT: return KeyboardKeycode::SDLK_CURRENCYSUBUNIT;
        case SDLK_KP_LEFTPAREN: return KeyboardKeycode::SDLK_KP_LEFTPAREN;
        case SDLK_KP_RIGHTPAREN: return KeyboardKeycode::SDLK_KP_RIGHTPAREN;
        case SDLK_KP_LEFTBRACE: return KeyboardKeycode::SDLK_KP_LEFTBRACE;
        case SDLK_KP_RIGHTBRACE: return KeyboardKeycode::SDLK_KP_RIGHTBRACE;
        case SDLK_KP_TAB: return KeyboardKeycode::SDLK_KP_TAB;
        case SDLK_KP_BACKSPACE: return KeyboardKeycode::SDLK_KP_BACKSPACE;
        case SDLK_KP_A: return KeyboardKeycode::SDLK_KP_A;
        case SDLK_KP_B: return KeyboardKeycode::SDLK_KP_B;
        case SDLK_KP_C: return KeyboardKeycode::SDLK_KP_C;
        case SDLK_KP_D: return KeyboardKeycode::SDLK_KP_D;
        case SDLK_KP_E: return KeyboardKeycode::SDLK_KP_E;
        case SDLK_KP_F: return KeyboardKeycode::SDLK_KP_F;
        case SDLK_KP_XOR: return KeyboardKeycode::SDLK_KP_XOR;
        case SDLK_KP_POWER: return KeyboardKeycode::SDLK_KP_POWER;
        case SDLK_KP_PERCENT: return KeyboardKeycode::SDLK_KP_PERCENT;
        case SDLK_KP_LESS: return KeyboardKeycode::SDLK_KP_LESS;
        case SDLK_KP_GREATER: return KeyboardKeycode::SDLK_KP_GREATER;
        case SDLK_KP_AMPERSAND: return KeyboardKeycode::SDLK_KP_AMPERSAND;
        case SDLK_KP_DBLAMPERSAND: return KeyboardKeycode::SDLK_KP_DBLAMPERSAND;
        case SDLK_KP_VERTICALBAR: return KeyboardKeycode::SDLK_KP_VERTICALBAR;
        case SDLK_KP_DBLVERTICALBAR: return KeyboardKeycode::SDLK_KP_DBLVERTICALBAR;
        case SDLK_KP_COLON: return KeyboardKeycode::SDLK_KP_COLON;
        case SDLK_KP_HASH: return KeyboardKeycode::SDLK_KP_HASH;
        case SDLK_KP_SPACE: return KeyboardKeycode::SDLK_KP_SPACE;
        case SDLK_KP_AT: return KeyboardKeycode::SDLK_KP_AT;
        case SDLK_KP_EXCLAM: return KeyboardKeycode::SDLK_KP_EXCLAM;
        case SDLK_KP_MEMSTORE: return KeyboardKeycode::SDLK_KP_MEMSTORE;
        case SDLK_KP_MEMRECALL: return KeyboardKeycode::SDLK_KP_MEMRECALL;
        case SDLK_KP_MEMCLEAR: return KeyboardKeycode::SDLK_KP_MEMCLEAR;
        case SDLK_KP_MEMADD: return KeyboardKeycode::SDLK_KP_MEMADD;
        case SDLK_KP_MEMSUBTRACT: return KeyboardKeycode::SDLK_KP_MEMSUBTRACT;
        case SDLK_KP_MEMMULTIPLY: return KeyboardKeycode::SDLK_KP_MEMMULTIPLY;
        case SDLK_KP_MEMDIVIDE: return KeyboardKeycode::SDLK_KP_MEMDIVIDE;
        case SDLK_KP_PLUSMINUS: return KeyboardKeycode::SDLK_KP_PLUSMINUS;
        case SDLK_KP_CLEAR: return KeyboardKeycode::SDLK_KP_CLEAR;
        case SDLK_KP_CLEARENTRY: return KeyboardKeycode::SDLK_KP_CLEARENTRY;
        case SDLK_KP_BINARY: return KeyboardKeycode::SDLK_KP_BINARY;
        case SDLK_KP_OCTAL: return KeyboardKeycode::SDLK_KP_OCTAL;
        case SDLK_KP_DECIMAL: return KeyboardKeycode::SDLK_KP_DECIMAL;
        case SDLK_KP_HEXADECIMAL: return KeyboardKeycode::SDLK_KP_HEXADECIMAL;
        case SDLK_LCTRL: return KeyboardKeycode::SDLK_LCTRL;
        case SDLK_LSHIFT: return KeyboardKeycode::SDLK_LSHIFT;
        case SDLK_LALT: return KeyboardKeycode::SDLK_LALT;
        case SDLK_LGUI: return KeyboardKeycode::SDLK_LGUI;
        case SDLK_RCTRL: return KeyboardKeycode::SDLK_RCTRL;
        case SDLK_RSHIFT: return KeyboardKeycode::SDLK_RSHIFT;
        case SDLK_RALT: return KeyboardKeycode::SDLK_RALT;
        case SDLK_RGUI: return KeyboardKeycode::SDLK_RGUI;
        case SDLK_MODE: return KeyboardKeycode::SDLK_MODE;
        case SDLK_AUDIONEXT: return KeyboardKeycode::SDLK_AUDIONEXT;
        case SDLK_AUDIOPREV: return KeyboardKeycode::SDLK_AUDIOPREV;
        case SDLK_AUDIOSTOP: return KeyboardKeycode::SDLK_AUDIOSTOP;
        case SDLK_AUDIOPLAY: return KeyboardKeycode::SDLK_AUDIOPLAY;
        case SDLK_AUDIOMUTE: return KeyboardKeycode::SDLK_AUDIOMUTE;
        case SDLK_MEDIASELECT: return KeyboardKeycode::SDLK_MEDIASELECT;
        case SDLK_WWW: return KeyboardKeycode::SDLK_WWW;
        case SDLK_MAIL: return KeyboardKeycode::SDLK_MAIL;
        case SDLK_CALCULATOR: return KeyboardKeycode::SDLK_CALCULATOR;
        case SDLK_COMPUTER: return KeyboardKeycode::SDLK_COMPUTER;
        case SDLK_AC_SEARCH: return KeyboardKeycode::SDLK_AC_SEARCH;
        case SDLK_AC_HOME: return KeyboardKeycode::SDLK_AC_HOME;
        case SDLK_AC_BACK: return KeyboardKeycode::SDLK_AC_BACK;
        case SDLK_AC_FORWARD: return KeyboardKeycode::SDLK_AC_FORWARD;
        case SDLK_AC_STOP: return KeyboardKeycode::SDLK_AC_STOP;
        case SDLK_AC_REFRESH: return KeyboardKeycode::SDLK_AC_REFRESH;
        case SDLK_AC_BOOKMARKS: return KeyboardKeycode::SDLK_AC_BOOKMARKS;
        case SDLK_BRIGHTNESSDOWN: return KeyboardKeycode::SDLK_BRIGHTNESSDOWN;
        case SDLK_BRIGHTNESSUP: return KeyboardKeycode::SDLK_BRIGHTNESSUP;
        case SDLK_DISPLAYSWITCH: return KeyboardKeycode::SDLK_DISPLAYSWITCH;
        case SDLK_KBDILLUMTOGGLE: return KeyboardKeycode::SDLK_KBDILLUMTOGGLE;
        case SDLK_KBDILLUMDOWN: return KeyboardKeycode::SDLK_KBDILLUMDOWN;
        case SDLK_KBDILLUMUP: return KeyboardKeycode::SDLK_KBDILLUMUP;
        case SDLK_EJECT: return KeyboardKeycode::SDLK_EJECT;
        case SDLK_SLEEP: return KeyboardKeycode::SDLK_SLEEP;
        default:
            return KeyboardKeycode::Unknown;
    }
}

ControllerDeviceEvent SuperSDLInputManager::ConvertControllerDeviceEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    // Which can be either Index or Controller Instance ID dependent on what happens,
    // On Add, it is index.
    // On Remove, it is instance ID.
    // In the next method "ConvertJoystickDeviceEventFromSDL" we sort this out.
    windowEvent.ControllerDevice.IndexID = event.cdevice.which;
    windowEvent.ControllerDevice.ControllerInstanceID = event.cdevice.which;
    windowEvent.ControllerDevice.Timestamp = event.cdevice.timestamp;

    windowEvent.ControllerDevice.Name = {};
    windowEvent.ControllerDevice.Axes = 0;
    windowEvent.ControllerDevice.Buttons = 0;

    return windowEvent.ControllerDevice;
}

JoystickDeviceEvent SuperSDLInputManager::ConvertJoystickDeviceEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    windowEvent.JoystickDevice.Timestamp = event.jdevice.timestamp;
    windowEvent.JoystickDevice.JoystickInstanceID = event.jdevice.which;

    return windowEvent.JoystickDevice;
}

JoyButtonEvent SuperSDLInputManager::ConvertJoyButtonEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    windowEvent.JoyButton.Type = windowEvent.EventType;
    windowEvent.JoyButton.Timestamp = event.jbutton.timestamp;
    windowEvent.JoyButton.Button = event.jbutton.button;
    windowEvent.JoyButton.InstanceID = event.jbutton.which;

    return windowEvent.JoyButton;
}

JoyHatEvent SuperSDLInputManager::ConvertJoyHatEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    windowEvent.JoyHat.Type = windowEvent.EventType;
    windowEvent.JoyHat.Timestamp = event.jhat.timestamp;
    windowEvent.JoyHat.ControllerInstanceID = event.jhat.which;
    windowEvent.JoyHat.HatIndex = event.jhat.hat;
    windowEvent.JoyHat.Position = HatPositionFromValue(event.jhat.value);

    return windowEvent.JoyHat;
}

JoyAxisEvent SuperSDLInputManager::ConvertJoyAxisEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    windowEvent.JoyAxis.Type = windowEvent.EventType;
    windowEvent.JoyAxis.Timestamp = event.jaxis.timestamp;
    windowEvent.JoyAxis.Value = event.jaxis.value;
    windowEvent.JoyAxis.Axis = event.jaxis.axis;
    windowEvent.JoyAxis.ControllerInstanceID = event.jaxis.which;

    return windowEvent.JoyAxis;
}

MouseButtonEvent SuperSDLInputManager::ConvertMouseButtonEventFromSDL(const SDL_Event& event, WindowEvent& windowEvent)
{
    windowEvent.MouseButton.Type = windowEvent.EventType;
    windowEvent.MouseButton.InstanceID = event.button.which;
    windowEvent.MouseButton.Clicks = event.button.clicks;
    windowEvent.MouseButton.Window = event.button.windowID;
    windowEvent.MouseButton.X = event.button.x;
    windowEvent.MouseButton.Y = event.button.y;
    windowEvent.MouseButton.Timestamp = event.button.timestamp;
    windowEvent.MouseButton.IsTouch = event.button.which == SDL_TOUCH_MOUSEID;
    windowEvent.MouseButton.Button = MouseButtonFromValue(event.button.button);

    return windowEvent.MouseButton;
}

void SuperSDLInputManager::UpdateOpenControllers(WindowEventType type, ControllerDeviceEvent& controllerDevice)
{
    if (type == WindowEventType::SDL_CONTROLLERDEVICEADDED)
    {
        size_t numberOfControllers = m_controllers.size();
        if (SDL_GameController* controller = OpenSDLControllerFromIndex(controllerDevice.IndexID))
        {
            SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
            controllerDevice.ControllerInstanceID = SDL_JoystickGetDeviceInstanceID(controllerDevice.ControllerInstanceID);
            controllerDevice.Name = SDL_JoystickName(joystick);
            controllerDevice.Axes = SDL_JoystickNumAxes(joystick);
            controllerDevice.Buttons = SDL_JoystickNumButtons(joystick);

            m_controllers.try_emplace(controllerDevice.ControllerInstanceID, controller);
        }
    }
    else if (type == WindowEventType::SDL_CONTROLLERDEVICEREMOVED)
    {
        SDL_GameController* controller = 
            m_controllers.contains(controllerDevice.ControllerInstanceID) ?
                m_controllers[controllerDevice.ControllerInstanceID] : nullptr;
        if (controller)
        {
            SDL_GameControllerClose(controller);
            m_controllers.erase(controllerDevice.ControllerInstanceID);
        }
    }
}

SDL_GameController* SuperSDLInputManager::OpenSDLControllerFromInstance(int instanceID)
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            SDL_JoystickID joystickID = SDL_JoystickGetDeviceInstanceID(i);
            if (instanceID == joystickID)
            {
                return SDL_GameControllerOpen(i);
            }
        }
    }

    return nullptr;
}

SDL_GameController* SuperSDLInputManager::OpenSDLControllerFromIndex(int index)
{
    if (SDL_NumJoysticks() >= index)
    {
        if (SDL_IsGameController(index))
        {
            return SDL_GameControllerOpen(index);
        }
    }

    return nullptr;
}

HatPosition SuperSDLInputManager::HatPositionFromValue(Uint8 hatValue)
{
    switch (hatValue)
    {
        case SDL_HAT_CENTERED: return HatPosition::CENTERED;
        case SDL_HAT_UP: return HatPosition::UP;
        case SDL_HAT_DOWN: return HatPosition::DOWN;
        case SDL_HAT_LEFT: return HatPosition::LEFT;
        case SDL_HAT_RIGHT: return HatPosition::RIGHT;
        case SDL_HAT_LEFTUP: return HatPosition::LEFTUP;
        case SDL_HAT_LEFTDOWN: return HatPosition::LEFTDOWN;
        case SDL_HAT_RIGHTUP: return HatPosition::RIGHTUP;
        case SDL_HAT_RIGHTDOWN: return HatPosition::RIGHTDOWN;
    }

    return HatPosition::Unknown;
}

MouseButton SuperSDLInputManager::MouseButtonFromValue(uint8_t mouseButtonValue)
{
    switch (mouseButtonValue)
    {
        case SDL_BUTTON_LEFT: return MouseButton::Left;
        case SDL_BUTTON_RIGHT: return MouseButton::Right;
        case SDL_BUTTON_MIDDLE: return MouseButton::Middle;
        case SDL_BUTTON_X1: return MouseButton::Back;
        case SDL_BUTTON_X2: return MouseButton::Forward;
        default:
            return MouseButton::Unknown;
    }
}
