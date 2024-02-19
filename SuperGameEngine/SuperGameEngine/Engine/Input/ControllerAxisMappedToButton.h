#pragma once
#include "UniversalControllerButton.hpp"
#include "ControllerAxisMappingEvaluation.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Maps an Axis to a button.
    /// Useful for Triggers which are not Axis (like Nintendo Switch Pro controller)
    /// or occasionally buttons just act like triggers.
    /// </summary>
    struct ControllerAxisMappedToButton
    {
        /// <summary>
        /// SDLAxis number.
        /// </summary>
        int Axis = -1;

        /// <summary>
        /// The button to map the Axis to.
        /// </summary>
        UniversalControllerButton Button = UniversalControllerButton::Unknown;

        /// <summary>
        /// How to evulate the number from the Axis to a true/false button value.
        /// </summary>
        ControllerAxisMappingEvaluation Evaluation;
    };
}