#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace SuperGameInput
{
    /// <summary>
    /// The types of events that can be delivered.
    /// </summary>
    enum class WindowEventType : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Unused (do not remove)
        /// </summary>
        SDL_FIRSTEVENT = 0,

        /// <summary>
        /// User-requested quit
        /// </summary>
        SDL_QUIT,

        /// <summary>
        /// The application is being terminated by the OS
        /// Called on iOS in applicationWillTerminate()
        /// Called on Android in onDestroy()
        /// </summary>
        SDL_APP_TERMINATING,

        /// <summary>
        /// The application is low on memory, free memory if possible.
        /// Called on iOS in applicationDidReceiveMemoryWarning()
        /// Called on Android in onLowMemory()
        /// </summary>
        SDL_APP_LOWMEMORY,

        /// <summary>
        /// The application is about to enter the background
        /// Called on iOS in applicationWillResignActive()
        /// Called on Android in onPause()
        /// </summary>
        SDL_APP_WILLENTERBACKGROUND,

        /// <summary>
        /// The application did enter the background and may not get CPU for some time
        /// Called on iOS in applicationDidEnterBackground()
        /// Called on Android in onPause()
        /// </summary>
        SDL_APP_DIDENTERBACKGROUND,

        /// <summary>
        /// The application is about to enter the foreground
        /// Called on iOS in applicationWillEnterForeground()
        /// Called on Android in onResume()
        /// </summary>
        SDL_APP_WILLENTERFOREGROUND,

        /// <summary>
        /// The application is now interactive
        /// Called on iOS in applicationDidBecomeActive()
        /// Called on Android in onResume()
        /// </summary>
        SDL_APP_DIDENTERFOREGROUND,

        /// <summary>
        /// The user's locale preferences have changed.
        /// </summary>
        SDL_LOCALECHANGED,

        /// <summary>
        /// Display state change
        /// </summary>
        SDL_DISPLAYEVENT,

        /// <summary>
        /// Window state change
        /// </summary>
        SDL_WINDOWEVENT,

        /// <summary>
        /// System specific event
        /// </summary>
        SDL_SYSWMEVENT,

        /// <summary>
        /// Key pressed
        /// </summary>
        SDL_KEYDOWN,

        /// <summary>
        /// Key released
        /// </summary>
        SDL_KEYUP,

        /// <summary>
        /// Keyboard text editing (composition)
        /// </summary>
        SDL_TEXTEDITING,

        /// <summary>
        /// Keyboard text input
        /// </summary>
        SDL_TEXTINPUT,

        /// <summary>
        /// Keymap changed due to a system event such as an
        /// input language or keyboard layout change.
        /// </summary>
        SDL_KEYMAPCHANGED,

        /// <summary>
        /// Extended keyboard text editing (composition)
        /// </summary>
        SDL_TEXTEDITING_EXT,

        /// <summary>
        /// Mouse moved
        /// </summary>
        SDL_MOUSEMOTION,

        /// <summary>
        /// Mouse button pressed
        /// </summary>
        SDL_MOUSEBUTTONDOWN,

        /// <summary>
        /// Mouse button released
        /// </summary>
        SDL_MOUSEBUTTONUP,

        /// <summary>
        /// Mouse wheel motion
        /// </summary>
        SDL_MOUSEWHEEL,

        /// <summary>
        /// Joystick axis motion
        /// </summary>
        SDL_JOYAXISMOTION,

        /// <summary>
        /// Joystick trackball motion
        /// </summary>
        SDL_JOYBALLMOTION,

        /// <summary>
        /// Joystick hat position change
        /// </summary>
        SDL_JOYHATMOTION,

        /// <summary>
        /// Joystick button pressed
        /// </summary>
        SDL_JOYBUTTONDOWN,

        /// <summary>
        /// Joystick button released
        /// </summary>
        SDL_JOYBUTTONUP,

        /// <summary>
        /// A new joystick has been inserted into the system
        /// </summary>
        SDL_JOYDEVICEADDED,

        /// <summary>
        /// An opened joystick has been removed
        /// </summary>
        SDL_JOYDEVICEREMOVED,

        /// <summary>
        /// Joystick battery level change
        /// </summary>
        SDL_JOYBATTERYUPDATED,

        /// <summary>
        /// Game controller axis motion
        /// </summary>
        SDL_CONTROLLERAXISMOTION,

        /// <summary>
        /// Game controller button pressed
        /// </summary>
        SDL_CONTROLLERBUTTONDOWN,

        /// <summary>
        /// Game controller button released
        /// </summary>
        SDL_CONTROLLERBUTTONUP,

        /// <summary>
        /// A new Game controller has been inserted into the system
        /// </summary>
        SDL_CONTROLLERDEVICEADDED,

        /// <summary>
        /// An opened Game controller has been removed
        /// </summary>
        SDL_CONTROLLERDEVICEREMOVED,

        /// <summary>
        /// The controller mapping was updated
        /// </summary>
        SDL_CONTROLLERDEVICEREMAPPED,

        /// <summary>
        /// Game controller touchpad was touched
        /// </summary>
        SDL_CONTROLLERTOUCHPADDOWN,

        /// <summary>
        /// Game controller touchpad finger was moved
        /// </summary>
        SDL_CONTROLLERTOUCHPADMOTION,

        /// <summary>
        /// Game controller touchpad finger was lifted
        /// </summary>
        SDL_CONTROLLERTOUCHPADUP,

        /// <summary>
        /// Game controller sensor was updated
        /// </summary>
        SDL_CONTROLLERSENSORUPDATE,

        SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,

        /// <summary>
        /// Game controller Steam handle has changed
        /// </summary>
        SDL_CONTROLLERSTEAMHANDLEUPDATED,

        SDL_FINGERDOWN,

        SDL_FINGERUP,

        SDL_FINGERMOTION,

        SDL_DOLLARGESTURE,

        SDL_DOLLARRECORD,

        SDL_MULTIGESTURE,

        /// <summary>
        /// The clipboard changed
        /// </summary>
        SDL_CLIPBOARDUPDATE,

        /// <summary>
        /// The system requests a file open
        /// </summary>
        SDL_DROPFILE,

        /// <summary>
        /// text/plain drag-and-drop event
        /// </summary>
        SDL_DROPTEXT,

        /// <summary>
        /// A new set of drops is beginning (NULL filename)
        /// </summary>
        SDL_DROPBEGIN,

        /// <summary>
        /// Current set of drops is now complete (NULL filename)
        /// </summary>
        SDL_DROPCOMPLETE,

        /// <summary>
        /// A new audio device is available
        /// </summary>
        SDL_AUDIODEVICEADDED,

        /// <summary>
        /// An audio device has been removed.
        /// </summary>
        SDL_AUDIODEVICEREMOVED,

        /// <summary>
        /// A sensor was updated
        /// </summary>
        SDL_SENSORUPDATE,

        /// <summary>
        /// The render targets have been reset and their contents need to be updated
        /// </summary>
        SDL_RENDER_TARGETS_RESET,

        /// <summary>
        /// The device has been reset and all textures need to be recreated
        /// </summary>
        SDL_RENDER_DEVICE_RESET,

        /// <summary>
        /// Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
        /// and should be allocated with SDL_RegisterEvents()
        /// </summary>
        SDL_USEREVENT,

        /// <summary>
        /// This last event is only for bounding internal arrays
        /// </summary>
        SDL_LASTEVENT,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EWindowEventType
    {
    public:
        static WindowEventType Min() { return WindowEventType::SDL_FIRSTEVENT; }
        static WindowEventType Max() { return WindowEventType::SDL_LASTEVENT; }

        static WindowEventType* ToArray()
        {
            static WindowEventType returnArray[] =
            {
                WindowEventType::SDL_FIRSTEVENT,
                WindowEventType::SDL_QUIT,
                WindowEventType::SDL_APP_TERMINATING,
                WindowEventType::SDL_APP_LOWMEMORY,
                WindowEventType::SDL_APP_WILLENTERBACKGROUND,
                WindowEventType::SDL_APP_DIDENTERBACKGROUND,
                WindowEventType::SDL_APP_WILLENTERFOREGROUND,
                WindowEventType::SDL_APP_DIDENTERFOREGROUND,
                WindowEventType::SDL_LOCALECHANGED,
                WindowEventType::SDL_DISPLAYEVENT,
                WindowEventType::SDL_WINDOWEVENT,
                WindowEventType::SDL_SYSWMEVENT,
                WindowEventType::SDL_KEYDOWN,
                WindowEventType::SDL_KEYUP,
                WindowEventType::SDL_TEXTEDITING,
                WindowEventType::SDL_TEXTINPUT,
                WindowEventType::SDL_KEYMAPCHANGED,
                WindowEventType::SDL_TEXTEDITING_EXT,
                WindowEventType::SDL_MOUSEMOTION,
                WindowEventType::SDL_MOUSEBUTTONDOWN,
                WindowEventType::SDL_MOUSEBUTTONUP,
                WindowEventType::SDL_MOUSEWHEEL,
                WindowEventType::SDL_JOYAXISMOTION,
                WindowEventType::SDL_JOYBALLMOTION,
                WindowEventType::SDL_JOYHATMOTION,
                WindowEventType::SDL_JOYBUTTONDOWN,
                WindowEventType::SDL_JOYBUTTONUP,
                WindowEventType::SDL_JOYDEVICEADDED,
                WindowEventType::SDL_JOYDEVICEREMOVED,
                WindowEventType::SDL_JOYBATTERYUPDATED,
                WindowEventType::SDL_CONTROLLERAXISMOTION,
                WindowEventType::SDL_CONTROLLERBUTTONDOWN,
                WindowEventType::SDL_CONTROLLERBUTTONUP,
                WindowEventType::SDL_CONTROLLERDEVICEADDED,
                WindowEventType::SDL_CONTROLLERDEVICEREMOVED,
                WindowEventType::SDL_CONTROLLERDEVICEREMAPPED,
                WindowEventType::SDL_CONTROLLERTOUCHPADDOWN,
                WindowEventType::SDL_CONTROLLERTOUCHPADMOTION,
                WindowEventType::SDL_CONTROLLERTOUCHPADUP,
                WindowEventType::SDL_CONTROLLERSENSORUPDATE,
                WindowEventType::SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
                WindowEventType::SDL_CONTROLLERSTEAMHANDLEUPDATED,
                WindowEventType::SDL_FINGERDOWN,
                WindowEventType::SDL_FINGERUP,
                WindowEventType::SDL_FINGERMOTION,
                WindowEventType::SDL_DOLLARGESTURE,
                WindowEventType::SDL_DOLLARRECORD,
                WindowEventType::SDL_MULTIGESTURE,
                WindowEventType::SDL_CLIPBOARDUPDATE,
                WindowEventType::SDL_DROPFILE,
                WindowEventType::SDL_DROPTEXT,
                WindowEventType::SDL_DROPBEGIN,
                WindowEventType::SDL_DROPCOMPLETE,
                WindowEventType::SDL_AUDIODEVICEADDED,
                WindowEventType::SDL_AUDIODEVICEREMOVED,
                WindowEventType::SDL_SENSORUPDATE,
                WindowEventType::SDL_RENDER_TARGETS_RESET,
                WindowEventType::SDL_RENDER_DEVICE_RESET,
                WindowEventType::SDL_USEREVENT,
                WindowEventType::SDL_LASTEVENT,
            };

            return returnArray;
        }

        static std::vector<WindowEventType> ToVector()
        {
            static std::vector<WindowEventType> returnVector =
            {
                WindowEventType::SDL_FIRSTEVENT,
                WindowEventType::SDL_QUIT,
                WindowEventType::SDL_APP_TERMINATING,
                WindowEventType::SDL_APP_LOWMEMORY,
                WindowEventType::SDL_APP_WILLENTERBACKGROUND,
                WindowEventType::SDL_APP_DIDENTERBACKGROUND,
                WindowEventType::SDL_APP_WILLENTERFOREGROUND,
                WindowEventType::SDL_APP_DIDENTERFOREGROUND,
                WindowEventType::SDL_LOCALECHANGED,
                WindowEventType::SDL_DISPLAYEVENT,
                WindowEventType::SDL_WINDOWEVENT,
                WindowEventType::SDL_SYSWMEVENT,
                WindowEventType::SDL_KEYDOWN,
                WindowEventType::SDL_KEYUP,
                WindowEventType::SDL_TEXTEDITING,
                WindowEventType::SDL_TEXTINPUT,
                WindowEventType::SDL_KEYMAPCHANGED,
                WindowEventType::SDL_TEXTEDITING_EXT,
                WindowEventType::SDL_MOUSEMOTION,
                WindowEventType::SDL_MOUSEBUTTONDOWN,
                WindowEventType::SDL_MOUSEBUTTONUP,
                WindowEventType::SDL_MOUSEWHEEL,
                WindowEventType::SDL_JOYAXISMOTION,
                WindowEventType::SDL_JOYBALLMOTION,
                WindowEventType::SDL_JOYHATMOTION,
                WindowEventType::SDL_JOYBUTTONDOWN,
                WindowEventType::SDL_JOYBUTTONUP,
                WindowEventType::SDL_JOYDEVICEADDED,
                WindowEventType::SDL_JOYDEVICEREMOVED,
                WindowEventType::SDL_JOYBATTERYUPDATED,
                WindowEventType::SDL_CONTROLLERAXISMOTION,
                WindowEventType::SDL_CONTROLLERBUTTONDOWN,
                WindowEventType::SDL_CONTROLLERBUTTONUP,
                WindowEventType::SDL_CONTROLLERDEVICEADDED,
                WindowEventType::SDL_CONTROLLERDEVICEREMOVED,
                WindowEventType::SDL_CONTROLLERDEVICEREMAPPED,
                WindowEventType::SDL_CONTROLLERTOUCHPADDOWN,
                WindowEventType::SDL_CONTROLLERTOUCHPADMOTION,
                WindowEventType::SDL_CONTROLLERTOUCHPADUP,
                WindowEventType::SDL_CONTROLLERSENSORUPDATE,
                WindowEventType::SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
                WindowEventType::SDL_CONTROLLERSTEAMHANDLEUPDATED,
                WindowEventType::SDL_FINGERDOWN,
                WindowEventType::SDL_FINGERUP,
                WindowEventType::SDL_FINGERMOTION,
                WindowEventType::SDL_DOLLARGESTURE,
                WindowEventType::SDL_DOLLARRECORD,
                WindowEventType::SDL_MULTIGESTURE,
                WindowEventType::SDL_CLIPBOARDUPDATE,
                WindowEventType::SDL_DROPFILE,
                WindowEventType::SDL_DROPTEXT,
                WindowEventType::SDL_DROPBEGIN,
                WindowEventType::SDL_DROPCOMPLETE,
                WindowEventType::SDL_AUDIODEVICEADDED,
                WindowEventType::SDL_AUDIODEVICEREMOVED,
                WindowEventType::SDL_SENSORUPDATE,
                WindowEventType::SDL_RENDER_TARGETS_RESET,
                WindowEventType::SDL_RENDER_DEVICE_RESET,
                WindowEventType::SDL_USEREVENT,
                WindowEventType::SDL_LASTEVENT,
            };

            return returnVector;
        }

        static std::string ToString(WindowEventType value)
        {
            switch (value)
            {
            case WindowEventType::Unknown: return "Unknown";
            case WindowEventType::SDL_FIRSTEVENT: return "SDL_FIRSTEVENT";
            case WindowEventType::SDL_QUIT: return "SDL_QUIT";
            case WindowEventType::SDL_APP_TERMINATING: return "SDL_APP_TERMINATING";
            case WindowEventType::SDL_APP_LOWMEMORY: return "SDL_APP_LOWMEMORY";
            case WindowEventType::SDL_APP_WILLENTERBACKGROUND: return "SDL_APP_WILLENTERBACKGROUND";
            case WindowEventType::SDL_APP_DIDENTERBACKGROUND: return "SDL_APP_DIDENTERBACKGROUND";
            case WindowEventType::SDL_APP_WILLENTERFOREGROUND: return "SDL_APP_WILLENTERFOREGROUND";
            case WindowEventType::SDL_APP_DIDENTERFOREGROUND: return "SDL_APP_DIDENTERFOREGROUND";
            case WindowEventType::SDL_LOCALECHANGED: return "SDL_LOCALECHANGED";
            case WindowEventType::SDL_DISPLAYEVENT: return "SDL_DISPLAYEVENT";
            case WindowEventType::SDL_WINDOWEVENT: return "SDL_WINDOWEVENT";
            case WindowEventType::SDL_SYSWMEVENT: return "SDL_SYSWMEVENT";
            case WindowEventType::SDL_KEYDOWN: return "SDL_KEYDOWN";
            case WindowEventType::SDL_KEYUP: return "SDL_KEYUP";
            case WindowEventType::SDL_TEXTEDITING: return "SDL_TEXTEDITING";
            case WindowEventType::SDL_TEXTINPUT: return "SDL_TEXTINPUT";
            case WindowEventType::SDL_KEYMAPCHANGED: return "SDL_KEYMAPCHANGED";
            case WindowEventType::SDL_TEXTEDITING_EXT: return "SDL_TEXTEDITING_EXT";
            case WindowEventType::SDL_MOUSEMOTION: return "SDL_MOUSEMOTION";
            case WindowEventType::SDL_MOUSEBUTTONDOWN: return "SDL_MOUSEBUTTONDOWN";
            case WindowEventType::SDL_MOUSEBUTTONUP: return "SDL_MOUSEBUTTONUP";
            case WindowEventType::SDL_MOUSEWHEEL: return "SDL_MOUSEWHEEL";
            case WindowEventType::SDL_JOYAXISMOTION: return "SDL_JOYAXISMOTION";
            case WindowEventType::SDL_JOYBALLMOTION: return "SDL_JOYBALLMOTION";
            case WindowEventType::SDL_JOYHATMOTION: return "SDL_JOYHATMOTION";
            case WindowEventType::SDL_JOYBUTTONDOWN: return "SDL_JOYBUTTONDOWN";
            case WindowEventType::SDL_JOYBUTTONUP: return "SDL_JOYBUTTONUP";
            case WindowEventType::SDL_JOYDEVICEADDED: return "SDL_JOYDEVICEADDED";
            case WindowEventType::SDL_JOYDEVICEREMOVED: return "SDL_JOYDEVICEREMOVED";
            case WindowEventType::SDL_JOYBATTERYUPDATED: return "SDL_JOYBATTERYUPDATED";
            case WindowEventType::SDL_CONTROLLERAXISMOTION: return "SDL_CONTROLLERAXISMOTION";
            case WindowEventType::SDL_CONTROLLERBUTTONDOWN: return "SDL_CONTROLLERBUTTONDOWN";
            case WindowEventType::SDL_CONTROLLERBUTTONUP: return "SDL_CONTROLLERBUTTONUP";
            case WindowEventType::SDL_CONTROLLERDEVICEADDED: return "SDL_CONTROLLERDEVICEADDED";
            case WindowEventType::SDL_CONTROLLERDEVICEREMOVED: return "SDL_CONTROLLERDEVICEREMOVED";
            case WindowEventType::SDL_CONTROLLERDEVICEREMAPPED: return "SDL_CONTROLLERDEVICEREMAPPED";
            case WindowEventType::SDL_CONTROLLERTOUCHPADDOWN: return "SDL_CONTROLLERTOUCHPADDOWN";
            case WindowEventType::SDL_CONTROLLERTOUCHPADMOTION: return "SDL_CONTROLLERTOUCHPADMOTION";
            case WindowEventType::SDL_CONTROLLERTOUCHPADUP: return "SDL_CONTROLLERTOUCHPADUP";
            case WindowEventType::SDL_CONTROLLERSENSORUPDATE: return "SDL_CONTROLLERSENSORUPDATE";
            case WindowEventType::SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3: return "SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3";
            case WindowEventType::SDL_CONTROLLERSTEAMHANDLEUPDATED: return "SDL_CONTROLLERSTEAMHANDLEUPDATED";
            case WindowEventType::SDL_FINGERDOWN: return "SDL_FINGERDOWN";
            case WindowEventType::SDL_FINGERUP: return "SDL_FINGERUP";
            case WindowEventType::SDL_FINGERMOTION: return "SDL_FINGERMOTION";
            case WindowEventType::SDL_DOLLARGESTURE: return "SDL_DOLLARGESTURE";
            case WindowEventType::SDL_DOLLARRECORD: return "SDL_DOLLARRECORD";
            case WindowEventType::SDL_MULTIGESTURE: return "SDL_MULTIGESTURE";
            case WindowEventType::SDL_CLIPBOARDUPDATE: return "SDL_CLIPBOARDUPDATE";
            case WindowEventType::SDL_DROPFILE: return "SDL_DROPFILE";
            case WindowEventType::SDL_DROPTEXT: return "SDL_DROPTEXT";
            case WindowEventType::SDL_DROPBEGIN: return "SDL_DROPBEGIN";
            case WindowEventType::SDL_DROPCOMPLETE: return "SDL_DROPCOMPLETE";
            case WindowEventType::SDL_AUDIODEVICEADDED: return "SDL_AUDIODEVICEADDED";
            case WindowEventType::SDL_AUDIODEVICEREMOVED: return "SDL_AUDIODEVICEREMOVED";
            case WindowEventType::SDL_SENSORUPDATE: return "SDL_SENSORUPDATE";
            case WindowEventType::SDL_RENDER_TARGETS_RESET: return "SDL_RENDER_TARGETS_RESET";
            case WindowEventType::SDL_RENDER_DEVICE_RESET: return "SDL_RENDER_DEVICE_RESET";
            case WindowEventType::SDL_USEREVENT: return "SDL_USEREVENT";
            case WindowEventType::SDL_LASTEVENT: return "SDL_LASTEVENT";
            }

            return "Unknown";
        }

        static WindowEventType FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return WindowEventType::Unknown;
                if (value == "SDL_FIRSTEVENT") return WindowEventType::SDL_FIRSTEVENT;
                if (value == "SDL_QUIT") return WindowEventType::SDL_QUIT;
                if (value == "SDL_APP_TERMINATING") return WindowEventType::SDL_APP_TERMINATING;
                if (value == "SDL_APP_LOWMEMORY") return WindowEventType::SDL_APP_LOWMEMORY;
                if (value == "SDL_APP_WILLENTERBACKGROUND") return WindowEventType::SDL_APP_WILLENTERBACKGROUND;
                if (value == "SDL_APP_DIDENTERBACKGROUND") return WindowEventType::SDL_APP_DIDENTERBACKGROUND;
                if (value == "SDL_APP_WILLENTERFOREGROUND") return WindowEventType::SDL_APP_WILLENTERFOREGROUND;
                if (value == "SDL_APP_DIDENTERFOREGROUND") return WindowEventType::SDL_APP_DIDENTERFOREGROUND;
                if (value == "SDL_LOCALECHANGED") return WindowEventType::SDL_LOCALECHANGED;
                if (value == "SDL_DISPLAYEVENT") return WindowEventType::SDL_DISPLAYEVENT;
                if (value == "SDL_WINDOWEVENT") return WindowEventType::SDL_WINDOWEVENT;
                if (value == "SDL_SYSWMEVENT") return WindowEventType::SDL_SYSWMEVENT;
                if (value == "SDL_KEYDOWN") return WindowEventType::SDL_KEYDOWN;
                if (value == "SDL_KEYUP") return WindowEventType::SDL_KEYUP;
                if (value == "SDL_TEXTEDITING") return WindowEventType::SDL_TEXTEDITING;
                if (value == "SDL_TEXTINPUT") return WindowEventType::SDL_TEXTINPUT;
                if (value == "SDL_KEYMAPCHANGED") return WindowEventType::SDL_KEYMAPCHANGED;
                if (value == "SDL_TEXTEDITING_EXT") return WindowEventType::SDL_TEXTEDITING_EXT;
                if (value == "SDL_MOUSEMOTION") return WindowEventType::SDL_MOUSEMOTION;
                if (value == "SDL_MOUSEBUTTONDOWN") return WindowEventType::SDL_MOUSEBUTTONDOWN;
                if (value == "SDL_MOUSEBUTTONUP") return WindowEventType::SDL_MOUSEBUTTONUP;
                if (value == "SDL_MOUSEWHEEL") return WindowEventType::SDL_MOUSEWHEEL;
                if (value == "SDL_JOYAXISMOTION") return WindowEventType::SDL_JOYAXISMOTION;
                if (value == "SDL_JOYBALLMOTION") return WindowEventType::SDL_JOYBALLMOTION;
                if (value == "SDL_JOYHATMOTION") return WindowEventType::SDL_JOYHATMOTION;
                if (value == "SDL_JOYBUTTONDOWN") return WindowEventType::SDL_JOYBUTTONDOWN;
                if (value == "SDL_JOYBUTTONUP") return WindowEventType::SDL_JOYBUTTONUP;
                if (value == "SDL_JOYDEVICEADDED") return WindowEventType::SDL_JOYDEVICEADDED;
                if (value == "SDL_JOYDEVICEREMOVED") return WindowEventType::SDL_JOYDEVICEREMOVED;
                if (value == "SDL_JOYBATTERYUPDATED") return WindowEventType::SDL_JOYBATTERYUPDATED;
                if (value == "SDL_CONTROLLERAXISMOTION") return WindowEventType::SDL_CONTROLLERAXISMOTION;
                if (value == "SDL_CONTROLLERBUTTONDOWN") return WindowEventType::SDL_CONTROLLERBUTTONDOWN;
                if (value == "SDL_CONTROLLERBUTTONUP") return WindowEventType::SDL_CONTROLLERBUTTONUP;
                if (value == "SDL_CONTROLLERDEVICEADDED") return WindowEventType::SDL_CONTROLLERDEVICEADDED;
                if (value == "SDL_CONTROLLERDEVICEREMOVED") return WindowEventType::SDL_CONTROLLERDEVICEREMOVED;
                if (value == "SDL_CONTROLLERDEVICEREMAPPED") return WindowEventType::SDL_CONTROLLERDEVICEREMAPPED;
                if (value == "SDL_CONTROLLERTOUCHPADDOWN") return WindowEventType::SDL_CONTROLLERTOUCHPADDOWN;
                if (value == "SDL_CONTROLLERTOUCHPADMOTION") return WindowEventType::SDL_CONTROLLERTOUCHPADMOTION;
                if (value == "SDL_CONTROLLERTOUCHPADUP") return WindowEventType::SDL_CONTROLLERTOUCHPADUP;
                if (value == "SDL_CONTROLLERSENSORUPDATE") return WindowEventType::SDL_CONTROLLERSENSORUPDATE;
                if (value == "SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3") return WindowEventType::SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3;
                if (value == "SDL_CONTROLLERSTEAMHANDLEUPDATED") return WindowEventType::SDL_CONTROLLERSTEAMHANDLEUPDATED;
                if (value == "SDL_FINGERDOWN") return WindowEventType::SDL_FINGERDOWN;
                if (value == "SDL_FINGERUP") return WindowEventType::SDL_FINGERUP;
                if (value == "SDL_FINGERMOTION") return WindowEventType::SDL_FINGERMOTION;
                if (value == "SDL_DOLLARGESTURE") return WindowEventType::SDL_DOLLARGESTURE;
                if (value == "SDL_DOLLARRECORD") return WindowEventType::SDL_DOLLARRECORD;
                if (value == "SDL_MULTIGESTURE") return WindowEventType::SDL_MULTIGESTURE;
                if (value == "SDL_CLIPBOARDUPDATE") return WindowEventType::SDL_CLIPBOARDUPDATE;
                if (value == "SDL_DROPFILE") return WindowEventType::SDL_DROPFILE;
                if (value == "SDL_DROPTEXT") return WindowEventType::SDL_DROPTEXT;
                if (value == "SDL_DROPBEGIN") return WindowEventType::SDL_DROPBEGIN;
                if (value == "SDL_DROPCOMPLETE") return WindowEventType::SDL_DROPCOMPLETE;
                if (value == "SDL_AUDIODEVICEADDED") return WindowEventType::SDL_AUDIODEVICEADDED;
                if (value == "SDL_AUDIODEVICEREMOVED") return WindowEventType::SDL_AUDIODEVICEREMOVED;
                if (value == "SDL_SENSORUPDATE") return WindowEventType::SDL_SENSORUPDATE;
                if (value == "SDL_RENDER_TARGETS_RESET") return WindowEventType::SDL_RENDER_TARGETS_RESET;
                if (value == "SDL_RENDER_DEVICE_RESET") return WindowEventType::SDL_RENDER_DEVICE_RESET;
                if (value == "SDL_USEREVENT") return WindowEventType::SDL_USEREVENT;
                if (value == "SDL_LASTEVENT") return WindowEventType::SDL_LASTEVENT;
            }
            else
            {
                std::string valueLower = ToLower(value);
                if (valueLower == "unknown") return WindowEventType::Unknown;
                if (valueLower == "sdl_firstevent") return WindowEventType::SDL_FIRSTEVENT;
                if (valueLower == "sdl_quit") return WindowEventType::SDL_QUIT;
                if (valueLower == "sdl_app_terminating") return WindowEventType::SDL_APP_TERMINATING;
                if (valueLower == "sdl_app_lowmemory") return WindowEventType::SDL_APP_LOWMEMORY;
                if (valueLower == "sdl_app_willenterbackground") return WindowEventType::SDL_APP_WILLENTERBACKGROUND;
                if (valueLower == "sdl_app_didenterbackground") return WindowEventType::SDL_APP_DIDENTERBACKGROUND;
                if (valueLower == "sdl_app_willenterforeground") return WindowEventType::SDL_APP_WILLENTERFOREGROUND;
                if (valueLower == "sdl_app_didenterforeground") return WindowEventType::SDL_APP_DIDENTERFOREGROUND;
                if (valueLower == "sdl_localechanged") return WindowEventType::SDL_LOCALECHANGED;
                if (valueLower == "sdl_displayevent") return WindowEventType::SDL_DISPLAYEVENT;
                if (valueLower == "sdl_windowevent") return WindowEventType::SDL_WINDOWEVENT;
                if (valueLower == "sdl_syswmevent") return WindowEventType::SDL_SYSWMEVENT;
                if (valueLower == "sdl_keydown") return WindowEventType::SDL_KEYDOWN;
                if (valueLower == "sdl_keyup") return WindowEventType::SDL_KEYUP;
                if (valueLower == "sdl_textediting") return WindowEventType::SDL_TEXTEDITING;
                if (valueLower == "sdl_textinput") return WindowEventType::SDL_TEXTINPUT;
                if (valueLower == "sdl_keymapchanged") return WindowEventType::SDL_KEYMAPCHANGED;
                if (valueLower == "sdl_textediting_ext") return WindowEventType::SDL_TEXTEDITING_EXT;
                if (valueLower == "sdl_mousemotion") return WindowEventType::SDL_MOUSEMOTION;
                if (valueLower == "sdl_mousebuttondown") return WindowEventType::SDL_MOUSEBUTTONDOWN;
                if (valueLower == "sdl_mousebuttonup") return WindowEventType::SDL_MOUSEBUTTONUP;
                if (valueLower == "sdl_mousewheel") return WindowEventType::SDL_MOUSEWHEEL;
                if (valueLower == "sdl_joyaxismotion") return WindowEventType::SDL_JOYAXISMOTION;
                if (valueLower == "sdl_joyballmotion") return WindowEventType::SDL_JOYBALLMOTION;
                if (valueLower == "sdl_joyhatmotion") return WindowEventType::SDL_JOYHATMOTION;
                if (valueLower == "sdl_joybuttondown") return WindowEventType::SDL_JOYBUTTONDOWN;
                if (valueLower == "sdl_joybuttonup") return WindowEventType::SDL_JOYBUTTONUP;
                if (valueLower == "sdl_joydeviceadded") return WindowEventType::SDL_JOYDEVICEADDED;
                if (valueLower == "sdl_joydeviceremoved") return WindowEventType::SDL_JOYDEVICEREMOVED;
                if (valueLower == "sdl_joybatteryupdated") return WindowEventType::SDL_JOYBATTERYUPDATED;
                if (valueLower == "sdl_controlleraxismotion") return WindowEventType::SDL_CONTROLLERAXISMOTION;
                if (valueLower == "sdl_controllerbuttondown") return WindowEventType::SDL_CONTROLLERBUTTONDOWN;
                if (valueLower == "sdl_controllerbuttonup") return WindowEventType::SDL_CONTROLLERBUTTONUP;
                if (valueLower == "sdl_controllerdeviceadded") return WindowEventType::SDL_CONTROLLERDEVICEADDED;
                if (valueLower == "sdl_controllerdeviceremoved") return WindowEventType::SDL_CONTROLLERDEVICEREMOVED;
                if (valueLower == "sdl_controllerdeviceremapped") return WindowEventType::SDL_CONTROLLERDEVICEREMAPPED;
                if (valueLower == "sdl_controllertouchpaddown") return WindowEventType::SDL_CONTROLLERTOUCHPADDOWN;
                if (valueLower == "sdl_controllertouchpadmotion") return WindowEventType::SDL_CONTROLLERTOUCHPADMOTION;
                if (valueLower == "sdl_controllertouchpadup") return WindowEventType::SDL_CONTROLLERTOUCHPADUP;
                if (valueLower == "sdl_controllersensorupdate") return WindowEventType::SDL_CONTROLLERSENSORUPDATE;
                if (valueLower == "sdl_controllerupdatecomplete_reserved_for_sdl3") return WindowEventType::SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3;
                if (valueLower == "sdl_controllersteamhandleupdated") return WindowEventType::SDL_CONTROLLERSTEAMHANDLEUPDATED;
                if (valueLower == "sdl_fingerdown") return WindowEventType::SDL_FINGERDOWN;
                if (valueLower == "sdl_fingerup") return WindowEventType::SDL_FINGERUP;
                if (valueLower == "sdl_fingermotion") return WindowEventType::SDL_FINGERMOTION;
                if (valueLower == "sdl_dollargesture") return WindowEventType::SDL_DOLLARGESTURE;
                if (valueLower == "sdl_dollarrecord") return WindowEventType::SDL_DOLLARRECORD;
                if (valueLower == "sdl_multigesture") return WindowEventType::SDL_MULTIGESTURE;
                if (valueLower == "sdl_clipboardupdate") return WindowEventType::SDL_CLIPBOARDUPDATE;
                if (valueLower == "sdl_dropfile") return WindowEventType::SDL_DROPFILE;
                if (valueLower == "sdl_droptext") return WindowEventType::SDL_DROPTEXT;
                if (valueLower == "sdl_dropbegin") return WindowEventType::SDL_DROPBEGIN;
                if (valueLower == "sdl_dropcomplete") return WindowEventType::SDL_DROPCOMPLETE;
                if (valueLower == "sdl_audiodeviceadded") return WindowEventType::SDL_AUDIODEVICEADDED;
                if (valueLower == "sdl_audiodeviceremoved") return WindowEventType::SDL_AUDIODEVICEREMOVED;
                if (valueLower == "sdl_sensorupdate") return WindowEventType::SDL_SENSORUPDATE;
                if (valueLower == "sdl_render_targets_reset") return WindowEventType::SDL_RENDER_TARGETS_RESET;
                if (valueLower == "sdl_render_device_reset") return WindowEventType::SDL_RENDER_DEVICE_RESET;
                if (valueLower == "sdl_userevent") return WindowEventType::SDL_USEREVENT;
                if (valueLower == "sdl_lastevent") return WindowEventType::SDL_LASTEVENT;
            }

            return WindowEventType::Unknown;
        }

        /// <summary>
        /// Converts to lower. Copy from StringHelpers to ensure Enum does not require
        /// any outside dependency. Although we could include a header, doing so restricts
        /// the project which holds StringHelpers.
        /// </summary>
        static std::string ToLower(const std::string& input)
        {
            std::string output = input;
            for (char& c : output)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    c = c - 'A' + 'a';
                }
            }
            return output;
        }
    };
}
