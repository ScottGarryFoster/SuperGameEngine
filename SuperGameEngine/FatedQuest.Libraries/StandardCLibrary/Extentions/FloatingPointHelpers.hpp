#pragma once
#include "../Object/Object.h"
#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Methods to help manage floats and doubles.
    /// </summary>
    class FloatingPointHelpers : public Object
    {
    public:
        /// <summary>
        /// Returns true if two floats are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// </summary>
        /// <returns>True means are equal. </return>
        inline static bool AreEqual(float left, float right)
        {
            // The places to be accurate within.
            float epsilon = 0.00001f;

            return std::abs(left - right) < epsilon;
        }
        
        /// <summary>
        /// Returns true if two double are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// </summary>
        /// <returns>True means are equal. </return>
        inline static bool AreEqual(double left, double right)
        {
            // The places to be accurate within.
            double epsilon = 0.00001;

            return std::abs(left - right) < epsilon;
        }
    };
}