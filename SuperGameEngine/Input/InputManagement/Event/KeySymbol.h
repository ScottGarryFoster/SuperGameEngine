#pragma once
#include "KeyboardKeycode.h"
#include "KeyScancode.h"

namespace SuperGameInput
{
    /// <summary>
    /// Describes a key from a low level.
    /// </summary>
    class KeySymbol
    {
    public:
        /// <summary>
        /// Describes the scancode for a key.
        /// </summary>
        KeyScancode ScanCode;

        /// <summary>
        /// Describes the keycode for a key.
        /// </summary>
        KeyboardKeycode Keycode;
    };
}
