#pragma once
#include "ControllerComparisonType.h"

namespace SuperGameInput
{
    /// <summary>
    /// The evaluation of a single axis.
    /// When taking in a value from the axis, what becomes a pass?
    /// Axis Comparison Value for instance 200 > Value
    /// </summary>
    struct ControllerAxisMappingEvaluation
    {
        /// <summary>
        /// How to compare.
        /// Axis Comparison Value for instance 200 > Value
        /// </summary>
        ControllerComparisonType Comparison = ControllerComparisonType::Unknown;

        /// <summary>
        /// Value to use.
        /// On Axis, 0 is the middle, -32767 one direction, 32767 the other.
        /// </summary>
        int Value = 0;
    };
}