#pragma once
#include "GeneralKeyState.h"
#include "KeyboardEventType.h"
#include "KeySymbol.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_KeyboardEvent"/> without the SDL.
    /// </summary>
    struct KeyboardEvent
    {
    public:
        /// <summary>
        /// Describes a key from a low level.
        /// </summary>
        KeySymbol Key;
    };
}


