#pragma once
#include <cstdint>
#include <unordered_map>

#include "KeyOrButtonState.h"
#include "../Event/MouseButton.h"

namespace SuperGameInput
{
    /// <summary>
    /// Describes the state of a mouse, where it is, what button is pressed.
    /// </summary>
    struct MouseState
    {
    public:
        /// <summary>
        /// The current state of the buttons.
        /// A button could have multiple states.
        /// </summary>
        std::unordered_map<MouseButton, KeyOrButtonState> ButtonState;

        /// <summary>
        /// Position X relative to the window.
        /// </summary>
        int32_t X;

        /// <summary>
        /// Position Y relative to the window.
        /// </summary>
        int32_t Y;
    };
}
