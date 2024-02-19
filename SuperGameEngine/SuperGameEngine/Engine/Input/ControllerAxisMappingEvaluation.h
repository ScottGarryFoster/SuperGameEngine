#pragma once
#include "UniversalControllerButton.hpp"
#include "ControllerComparisonType.hpp"

namespace SuperGameEngine
{
    /// <summary>
    /// The evaluation of a single axis.
    /// When taking in a value from the axis, what becomes a pass?
    /// Axis Comparison Value for instance 200 > Value
    /// </summary>
    struct ControllerAxisMappingEvaluation
    {
        ControllerComparisonType Comparison = ControllerComparisonType::Unknown;
        int Value = 0;
    };
}