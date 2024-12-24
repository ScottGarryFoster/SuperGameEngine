#pragma once
#include <memory>
#include <string>
#include <vector>

namespace FatedQuestLibraries
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
        static bool RemoveValue(std::vector<T>& vector, const T& valueToRemove)
        {
            auto it = std::find(vector.begin(), vector.end(), valueToRemove);
            if (it != vector.end())
            {
                vector.erase(it);
                return true;
            }

            return false;
        }

        /// <summary>
        /// Removes the given value from the vector.
        /// </summary>
        /// <typeparam name="T">Type for the vector.</typeparam>
        /// <param name="vector">Vector to remove from. </param>
        /// <param name="valueToRemove">Value to remove from Vector. </param>
        /// <return>True means value found and removed. </return>
        template<typename T>
        static bool RemoveValue(std::vector<std::weak_ptr<T>>& vector, const std::weak_ptr <T>& valueToRemove)
        {
            // Find the value we are looking for as a shared pointer
            // Remove if will return a pointer to the elements to remove (after moving them to end)
            // or just return the end of the vector.
            auto it = std::remove_if(
                vector.begin(), vector.end(), [&valueToRemove](const std::weak_ptr<T>& weakPointer)
                {
                    if (auto sharedPointer = weakPointer.lock())
                    {
                        auto sharedPointerToRemove = valueToRemove.lock();
                        if (sharedPointer && sharedPointerToRemove)
                        {
                            return sharedPointer == sharedPointerToRemove;
                        }
                    }

                    return false;
                });

            // Actually remove it provided that is posible.
            if (it != vector.end())
            {
                vector.erase(it, vector.end());
                return true;
            }

            return false;
        }

        /// <summary>
        /// Removes value at the given index.
        /// </summary>
        /// <typeparam name="T">Type for the vector.</typeparam>
        /// <param name="vector">Vector to remove from. </param>
        /// <param name="index">Index to remove. </param>
        /// <returns>True means the index was found and removed. </returns>
        template<typename T>
        static bool RemoveAt(std::vector<T>& vector, size_t index)
        {
            if (index < vector.size())
            {
                vector.erase(vector.begin() + index);
                return true;
            }

            return false;
        }

        /// <summary>
        /// Does vector contain the given type?
        /// </summary>
        /// <typeparam name="T">Type of vector and entries. </typeparam>
        /// <param name="data">Collection. </param>
        /// <param name="lookFor">Type to lookfor. </param>
        /// <returns>True means does contain. </returns>
        template<typename T>
        static inline bool Contains(const std::vector<T>& data, const T& lookFor)
        {
            for (const auto& entry : data)
            {
                if (entry == lookFor)
                {
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Vector contains string.
        /// Might be more performant in certain situations.
        /// </summary>
        /// <param name="data">Collection of string. </param>
        /// <param name="lookFor">String to look for. </param>
        /// <returns>True means does contain. </returns>
        static bool ContainsString(const std::vector<std::string>& data, const std::string& lookFor);
    };
}

