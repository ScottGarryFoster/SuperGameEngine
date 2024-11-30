#pragma once

namespace FatedQuestLibraries
{
    /// <summary>
    /// Methods to help manage floats and doubles.
    /// </summary>
    class FloatingPointHelpers
    {
    public:
        /// <summary>
        /// Returns true if two floats are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// </summary>
        /// <returns>True means are equal. </return>
        inline static bool AreEqual(float left, float right);

        /// <summary>
        /// Returns true if two double are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// </summary>
        /// <returns>True means are equal. </return>
        inline static bool AreEqual(double left, double right);
    };
}