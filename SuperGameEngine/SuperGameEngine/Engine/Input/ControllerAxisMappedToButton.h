#pragma once
#include "UniversalControllerButton.hpp"
#include "ControllerAxisMappingEvaluation.h"

namespace SuperGameEngine
{

    struct ControllerAxisMappedToButton
    {
        int Axis;
        UniversalControllerButton Button;
        ControllerAxisMappingEvaluation Evaluation;
    };
}