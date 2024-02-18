#pragma once
#include "UniversalControllerButton.hpp"
#include "ControllerAxisMappingEvaluation.h"

namespace SuperGameEngine
{

    struct ControllerAxisMappedToButton
    {
        int Axis = -1;
        UniversalControllerButton Button = UniversalControllerButton::Unknown;
        ControllerAxisMappingEvaluation Evaluation;
    };
}