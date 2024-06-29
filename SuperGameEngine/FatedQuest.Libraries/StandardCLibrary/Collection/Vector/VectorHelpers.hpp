#pragma once
#include "../../Text/StringHelpers.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <string>

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
        /// <param name="caseSensitive">True means case must match. </param>
        /// <returns>True means does contain. </returns>
        static inline bool ContainsString(const std::vector<std::string>& data, const std::string& lookFor, bool caseSensitive = true)
        {
            std::string lowerLookFor = std::string();
            if (!caseSensitive)
            {
                // Avoid doing this if we do not need to.
                lowerLookFor = StringHelpers::ToLower(lookFor);
            }

            size_t lookForLength = lookFor.size();
            for (const std::string& entry : data)
            {
                if (entry.size() != lookForLength)
                {
                    continue;
                }

                if (caseSensitive)
                {
                    if (entry == lookFor)
                    {
                        return true;
                    }
                }
                else
                {
                    if (StringHelpers::ToLower(entry) == lowerLookFor)
                    {
                        return true;
                    }
                }

            }

            return false;
        }

        /// <summary>
        /// Looks for the given within the vector.
        /// Returns the Index so you can access the data.
        /// </summary>
        /// <typeparam name="T">Type stored in the Vector. </typeparam>
        /// <param name="data">Data to search. </param>
        /// <param name="lookFor">T to look for. </param>
        /// <returns>The index of the found data or -1 if not found. </returns>
        template<typename T>
        static inline size_t Find(const std::vector<T>& data, const T& lookFor)
        {
            for (size_t i = 0; i < data.size(); ++i)
            {
                if (data[i] == lookFor)
                {
                    return i;
                }
            }

            return -1;
        }

        /// <summary>
        /// Removes element at the given index if posible.
        /// </summary>
        /// <typeparam name="T">Type for the vector. </typeparam>
        /// <param name="data">Vector to remove from. </param>
        /// <param name="index">Index to remove. </param>
        /// <returns>True means could remove. </returns>
        template<typename T>
        static inline bool RemoveElementAtIndex(std::vector<T>& data, size_t index)
        {
            bool didRemove = false;
            if (index < data.size())
            {
                data.erase(data.begin() + index);
                didRemove = true;
            }

            return didRemove;
        }

        /// <summary>
        /// Remove and element at the given index if posible.
        /// The only way to check with this version is by checking the size decreased.
        /// </summary>
        /// <typeparam name="T">Type for the vector. </typeparam>
        /// <param name="data">Vector to remove from. </param>
        /// <param name="index">Index to remove. </param>
        /// <returns>Vector one smaller if successful. </returns>
        template<typename T>
        static inline std::vector<T> ReturnVectorWithElementRemovedAtIndex(const std::vector<T>& data, size_t index)
        {
            std::vector<T> returnVector = data;
            if (index < returnVector.size())
            {
                returnVector.erase(returnVector.begin() + index);
            }

            return returnVector;
        }

        /// <summary>
        /// Remove and element at the given index if posible.
        /// </summary>
        /// <typeparam name="T">Type for the vector. </typeparam>
        /// <param name="data">Vector to remove from. </param>
        /// <param name="index">Index to remove. </param>
        /// <param name="didRemove">True means did remove. </param>
        /// <returns>Vector one smaller if successful. </returns>
        template<typename T>
        static inline std::vector<T> ReturnVectorWithElementRemovedAtIndex(const std::vector<T>& data, size_t index, bool& didRemove)
        {
            didRemove = false;
            std::vector<T> returnVector = data;
            if (index < returnVector.size())
            {
                returnVector.erase(returnVector.begin() + index);
                didRemove = true;
            }

            return returnVector;
        }
    };
}