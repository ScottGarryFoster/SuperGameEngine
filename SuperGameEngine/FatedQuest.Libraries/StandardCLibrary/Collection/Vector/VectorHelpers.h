#pragma once
#include <vector>

namespace StandardCLibrary
{
    /// <summary>
    /// A collection of helper methods for manipulating vectors.
    /// </summary>
    class VectorHelpers
    {
    public:
        /// <summary>
        /// Removes the given value from the vector.
        /// </summary>
        /// <typeparam name="T">Type for the vector.</typeparam>
        /// <param name="vector">Vector to remove from. </param>
        /// <param name="valueToRemove">Value to remove from Vector. </param>
        /// <return>True means value found and removed. </return>
        template<typename T>
        static bool RemoveValue(std::vector<T>& vector, const T& valueToRemove);

        /// <summary>
        /// Removes value at the given index.
        /// </summary>
        /// <typeparam name="T">Type for the vector.</typeparam>
        /// <param name="vector">Vector to remove from. </param>
        /// <param name="index">Index to remove. </param>
        /// <returns>True means the index was found and removed. </returns>
        template<typename T>
        static bool RemoveAt(std::vector<T>& vector, size_t index);
    };
}