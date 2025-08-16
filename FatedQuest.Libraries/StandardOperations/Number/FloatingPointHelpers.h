#pragma once

namespace FatedQuestLibraries
{
    /// <summary>
    /// Methods to help manage floats and doubles.
    /// </summary>
    /// <remarks>
    /// In the case of the equals methods used in this class, equals is approximate,
    /// as floating point equality is not always to be trusted.
    /// Numbers must be equal within 5pts.
    /// 1.000001f == 1 = true but 1.00001f == 1 = false.
    /// </remarks>
    class FloatingPointHelpers
    {
    public:
        /// <summary>
        /// Returns true if two floats are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(float left, float right);

        /// <summary>
        /// Returns true if two double are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(double left, double right);

        /// <summary>
        /// Returns true if two numbers are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(float left, double right);

        /// <summary>
        /// Returns true if two numbers are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(double left, float right);

        /// <summary>
        /// Returns true if two numbers are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(float left, int right);

        /// <summary>
        /// Returns true if two numbers are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(int left, float right);

        /// <summary>
        /// Returns true if two numbers are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(double left, int right);

        /// <summary>
        /// Returns true if two numbers are approximately equal.
        /// </summary>
        /// <returns>True means are equal. </return>
        static bool AreEqual(int left, double right);

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