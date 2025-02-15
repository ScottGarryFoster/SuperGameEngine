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
    /// Event subtype for window events
    /// </summary>
    enum class WindowUpdateEventID : uint8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = 0,

        /// <summary>
        /// Never used
        /// </summary>
        SDL_WINDOWEVENT_NONE,

        /// <summary>
        /// Window has been shown
        /// </summary>
        SDL_WINDOWEVENT_SHOWN,

        /// <summary>
        /// Window has been hidden
        /// </summary>
        SDL_WINDOWEVENT_HIDDEN,

        /// <summary>
        /// Window has been exposed and should be redrawn
        /// </summary>
        SDL_WINDOWEVENT_EXPOSED,

        /// <summary>
        /// Window has been moved to data1, data2
        /// </summary>
        SDL_WINDOWEVENT_MOVED,

        /// <summary>
        /// Window has been resized to data1xdata2
        /// </summary>
        SDL_WINDOWEVENT_RESIZED,

        /// <summary>
        /// The window size has changed, either as a result of an API call
        /// or through the system or user changing the window size.
        /// </summary>
        SDL_WINDOWEVENT_SIZE_CHANGED,

        /// <summary>
        /// Window has been minimized
        /// </summary>
        SDL_WINDOWEVENT_MINIMIZED,

        /// <summary>
        /// Window has been maximized
        /// </summary>
        SDL_WINDOWEVENT_MAXIMIZED,

        /// <summary>
        /// Window has been restored to normal size and position
        /// </summary>
        SDL_WINDOWEVENT_RESTORED,

        /// <summary>
        /// Window has gained mouse focus
        /// </summary>
        SDL_WINDOWEVENT_ENTER,

        /// <summary>
        /// Window has lost mouse focus
        /// </summary>
        SDL_WINDOWEVENT_LEAVE,

        /// <summary>
        /// Window has gained keyboard focus
        /// </summary>
        SDL_WINDOWEVENT_FOCUS_GAINED,

        /// <summary>
        /// Window has lost keyboard focus
        /// </summary>
        SDL_WINDOWEVENT_FOCUS_LOST,

        /// <summary>
        /// The window manager requests that the window be closed
        /// </summary>
        SDL_WINDOWEVENT_CLOSE,

        /// <summary>
        /// Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore)
        /// </summary>
        SDL_WINDOWEVENT_TAKE_FOCUS,

        /// <summary>
        /// Window had a hit test that wasn't SDL_HITTEST_NORMAL.
        /// </summary>
        SDL_WINDOWEVENT_HIT_TEST,

        /// <summary>
        /// The ICC profile of the window's display has changed.
        /// </summary>
        SDL_WINDOWEVENT_ICCPROF_CHANGED,

        /// <summary>
        /// Window has been moved to display data1.
        /// </summary>
        SDL_WINDOWEVENT_DISPLAY_CHANGED,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EWindowUpdateEventID
    {
    public:
        static WindowUpdateEventID Min() { return WindowUpdateEventID::SDL_WINDOWEVENT_NONE; }
        static WindowUpdateEventID Max() { return WindowUpdateEventID::SDL_WINDOWEVENT_DISPLAY_CHANGED; }

        static WindowUpdateEventID* ToArray()
        {
            static WindowUpdateEventID returnArray[] =
            {
                WindowUpdateEventID::SDL_WINDOWEVENT_NONE,
                WindowUpdateEventID::SDL_WINDOWEVENT_SHOWN,
                WindowUpdateEventID::SDL_WINDOWEVENT_HIDDEN,
                WindowUpdateEventID::SDL_WINDOWEVENT_EXPOSED,
                WindowUpdateEventID::SDL_WINDOWEVENT_MOVED,
                WindowUpdateEventID::SDL_WINDOWEVENT_RESIZED,
                WindowUpdateEventID::SDL_WINDOWEVENT_SIZE_CHANGED,
                WindowUpdateEventID::SDL_WINDOWEVENT_MINIMIZED,
                WindowUpdateEventID::SDL_WINDOWEVENT_MAXIMIZED,
                WindowUpdateEventID::SDL_WINDOWEVENT_RESTORED,
                WindowUpdateEventID::SDL_WINDOWEVENT_ENTER,
                WindowUpdateEventID::SDL_WINDOWEVENT_LEAVE,
                WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_GAINED,
                WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_LOST,
                WindowUpdateEventID::SDL_WINDOWEVENT_CLOSE,
                WindowUpdateEventID::SDL_WINDOWEVENT_TAKE_FOCUS,
                WindowUpdateEventID::SDL_WINDOWEVENT_HIT_TEST,
                WindowUpdateEventID::SDL_WINDOWEVENT_ICCPROF_CHANGED,
                WindowUpdateEventID::SDL_WINDOWEVENT_DISPLAY_CHANGED,
            };
            
            return returnArray;
        }

        static std::vector<WindowUpdateEventID> ToVector()
        {
            static std::vector<WindowUpdateEventID> returnVector =
            {
                WindowUpdateEventID::SDL_WINDOWEVENT_NONE,
                WindowUpdateEventID::SDL_WINDOWEVENT_SHOWN,
                WindowUpdateEventID::SDL_WINDOWEVENT_HIDDEN,
                WindowUpdateEventID::SDL_WINDOWEVENT_EXPOSED,
                WindowUpdateEventID::SDL_WINDOWEVENT_MOVED,
                WindowUpdateEventID::SDL_WINDOWEVENT_RESIZED,
                WindowUpdateEventID::SDL_WINDOWEVENT_SIZE_CHANGED,
                WindowUpdateEventID::SDL_WINDOWEVENT_MINIMIZED,
                WindowUpdateEventID::SDL_WINDOWEVENT_MAXIMIZED,
                WindowUpdateEventID::SDL_WINDOWEVENT_RESTORED,
                WindowUpdateEventID::SDL_WINDOWEVENT_ENTER,
                WindowUpdateEventID::SDL_WINDOWEVENT_LEAVE,
                WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_GAINED,
                WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_LOST,
                WindowUpdateEventID::SDL_WINDOWEVENT_CLOSE,
                WindowUpdateEventID::SDL_WINDOWEVENT_TAKE_FOCUS,
                WindowUpdateEventID::SDL_WINDOWEVENT_HIT_TEST,
                WindowUpdateEventID::SDL_WINDOWEVENT_ICCPROF_CHANGED,
                WindowUpdateEventID::SDL_WINDOWEVENT_DISPLAY_CHANGED,
            };
            
            return returnVector;
        }

        static std::string ToString(WindowUpdateEventID value)
        {
            switch (value)
            {
                case WindowUpdateEventID::Unknown: return "Unknown";
                case WindowUpdateEventID::SDL_WINDOWEVENT_NONE: return "SDL_WINDOWEVENT_NONE";
                case WindowUpdateEventID::SDL_WINDOWEVENT_SHOWN: return "SDL_WINDOWEVENT_SHOWN";
                case WindowUpdateEventID::SDL_WINDOWEVENT_HIDDEN: return "SDL_WINDOWEVENT_HIDDEN";
                case WindowUpdateEventID::SDL_WINDOWEVENT_EXPOSED: return "SDL_WINDOWEVENT_EXPOSED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_MOVED: return "SDL_WINDOWEVENT_MOVED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_RESIZED: return "SDL_WINDOWEVENT_RESIZED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_SIZE_CHANGED: return "SDL_WINDOWEVENT_SIZE_CHANGED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_MINIMIZED: return "SDL_WINDOWEVENT_MINIMIZED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_MAXIMIZED: return "SDL_WINDOWEVENT_MAXIMIZED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_RESTORED: return "SDL_WINDOWEVENT_RESTORED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_ENTER: return "SDL_WINDOWEVENT_ENTER";
                case WindowUpdateEventID::SDL_WINDOWEVENT_LEAVE: return "SDL_WINDOWEVENT_LEAVE";
                case WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_GAINED: return "SDL_WINDOWEVENT_FOCUS_GAINED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_LOST: return "SDL_WINDOWEVENT_FOCUS_LOST";
                case WindowUpdateEventID::SDL_WINDOWEVENT_CLOSE: return "SDL_WINDOWEVENT_CLOSE";
                case WindowUpdateEventID::SDL_WINDOWEVENT_TAKE_FOCUS: return "SDL_WINDOWEVENT_TAKE_FOCUS";
                case WindowUpdateEventID::SDL_WINDOWEVENT_HIT_TEST: return "SDL_WINDOWEVENT_HIT_TEST";
                case WindowUpdateEventID::SDL_WINDOWEVENT_ICCPROF_CHANGED: return "SDL_WINDOWEVENT_ICCPROF_CHANGED";
                case WindowUpdateEventID::SDL_WINDOWEVENT_DISPLAY_CHANGED: return "SDL_WINDOWEVENT_DISPLAY_CHANGED";
            }
            
            return "Unknown";
        }

        static WindowUpdateEventID FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return WindowUpdateEventID::Unknown;
                if (value == "SDL_WINDOWEVENT_NONE") return WindowUpdateEventID::SDL_WINDOWEVENT_NONE;
                if (value == "SDL_WINDOWEVENT_SHOWN") return WindowUpdateEventID::SDL_WINDOWEVENT_SHOWN;
                if (value == "SDL_WINDOWEVENT_HIDDEN") return WindowUpdateEventID::SDL_WINDOWEVENT_HIDDEN;
                if (value == "SDL_WINDOWEVENT_EXPOSED") return WindowUpdateEventID::SDL_WINDOWEVENT_EXPOSED;
                if (value == "SDL_WINDOWEVENT_MOVED") return WindowUpdateEventID::SDL_WINDOWEVENT_MOVED;
                if (value == "SDL_WINDOWEVENT_RESIZED") return WindowUpdateEventID::SDL_WINDOWEVENT_RESIZED;
                if (value == "SDL_WINDOWEVENT_SIZE_CHANGED") return WindowUpdateEventID::SDL_WINDOWEVENT_SIZE_CHANGED;
                if (value == "SDL_WINDOWEVENT_MINIMIZED") return WindowUpdateEventID::SDL_WINDOWEVENT_MINIMIZED;
                if (value == "SDL_WINDOWEVENT_MAXIMIZED") return WindowUpdateEventID::SDL_WINDOWEVENT_MAXIMIZED;
                if (value == "SDL_WINDOWEVENT_RESTORED") return WindowUpdateEventID::SDL_WINDOWEVENT_RESTORED;
                if (value == "SDL_WINDOWEVENT_ENTER") return WindowUpdateEventID::SDL_WINDOWEVENT_ENTER;
                if (value == "SDL_WINDOWEVENT_LEAVE") return WindowUpdateEventID::SDL_WINDOWEVENT_LEAVE;
                if (value == "SDL_WINDOWEVENT_FOCUS_GAINED") return WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_GAINED;
                if (value == "SDL_WINDOWEVENT_FOCUS_LOST") return WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_LOST;
                if (value == "SDL_WINDOWEVENT_CLOSE") return WindowUpdateEventID::SDL_WINDOWEVENT_CLOSE;
                if (value == "SDL_WINDOWEVENT_TAKE_FOCUS") return WindowUpdateEventID::SDL_WINDOWEVENT_TAKE_FOCUS;
                if (value == "SDL_WINDOWEVENT_HIT_TEST") return WindowUpdateEventID::SDL_WINDOWEVENT_HIT_TEST;
                if (value == "SDL_WINDOWEVENT_ICCPROF_CHANGED") return WindowUpdateEventID::SDL_WINDOWEVENT_ICCPROF_CHANGED;
                if (value == "SDL_WINDOWEVENT_DISPLAY_CHANGED") return WindowUpdateEventID::SDL_WINDOWEVENT_DISPLAY_CHANGED;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return WindowUpdateEventID::Unknown;
                if (valueLower == "sdl_windowevent_none") return WindowUpdateEventID::SDL_WINDOWEVENT_NONE;
                if (valueLower == "sdl_windowevent_shown") return WindowUpdateEventID::SDL_WINDOWEVENT_SHOWN;
                if (valueLower == "sdl_windowevent_hidden") return WindowUpdateEventID::SDL_WINDOWEVENT_HIDDEN;
                if (valueLower == "sdl_windowevent_exposed") return WindowUpdateEventID::SDL_WINDOWEVENT_EXPOSED;
                if (valueLower == "sdl_windowevent_moved") return WindowUpdateEventID::SDL_WINDOWEVENT_MOVED;
                if (valueLower == "sdl_windowevent_resized") return WindowUpdateEventID::SDL_WINDOWEVENT_RESIZED;
                if (valueLower == "sdl_windowevent_size_changed") return WindowUpdateEventID::SDL_WINDOWEVENT_SIZE_CHANGED;
                if (valueLower == "sdl_windowevent_minimized") return WindowUpdateEventID::SDL_WINDOWEVENT_MINIMIZED;
                if (valueLower == "sdl_windowevent_maximized") return WindowUpdateEventID::SDL_WINDOWEVENT_MAXIMIZED;
                if (valueLower == "sdl_windowevent_restored") return WindowUpdateEventID::SDL_WINDOWEVENT_RESTORED;
                if (valueLower == "sdl_windowevent_enter") return WindowUpdateEventID::SDL_WINDOWEVENT_ENTER;
                if (valueLower == "sdl_windowevent_leave") return WindowUpdateEventID::SDL_WINDOWEVENT_LEAVE;
                if (valueLower == "sdl_windowevent_focus_gained") return WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_GAINED;
                if (valueLower == "sdl_windowevent_focus_lost") return WindowUpdateEventID::SDL_WINDOWEVENT_FOCUS_LOST;
                if (valueLower == "sdl_windowevent_close") return WindowUpdateEventID::SDL_WINDOWEVENT_CLOSE;
                if (valueLower == "sdl_windowevent_take_focus") return WindowUpdateEventID::SDL_WINDOWEVENT_TAKE_FOCUS;
                if (valueLower == "sdl_windowevent_hit_test") return WindowUpdateEventID::SDL_WINDOWEVENT_HIT_TEST;
                if (valueLower == "sdl_windowevent_iccprof_changed") return WindowUpdateEventID::SDL_WINDOWEVENT_ICCPROF_CHANGED;
                if (valueLower == "sdl_windowevent_display_changed") return WindowUpdateEventID::SDL_WINDOWEVENT_DISPLAY_CHANGED;
            }
            
            return WindowUpdateEventID::Unknown;
        }

        /// <summary>
        /// Converts to lower. Copy from StringHelpers to ensure Enum does not require
        /// any outside dependency. Although we could include a header, doing so restricts
        /// the project which holds StringHelpers.
        /// </summary>
        static std::string ToLower(const std::string & input)
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
