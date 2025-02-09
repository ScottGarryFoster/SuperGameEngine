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
        static bool AreEqual(float left, float right);

        /// <summary>
        /// Returns true if two double are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(double left, double right);

        /// <summary>
        /// Divide without actually dividing.
        /// Slightly more efficient than regular division.
        /// </summary>
        /// <param name="dividend">Number to divide. </param>
        /// <param name="divisor">Number to divide by. </param>
        /// <returns>Result. </returns>
        static float Divide(float dividend, float divisor);
    };
}