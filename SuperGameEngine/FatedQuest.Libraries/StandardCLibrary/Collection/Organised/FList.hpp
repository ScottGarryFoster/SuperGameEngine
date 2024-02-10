#pragma once

#include "FCollection.hpp"

namespace StandardCLibrary
{
    /// <summary>
    /// Data stored as a set.
    /// </summary>
    template<typename T>
    class FList : public FCollection<T>
    {
    public:
        FList() : FCollection<T>() {}
        FList(const T& value) : FCollection<T>(value) {}
        FList(const std::vector<T> values) : FCollection<T>(values) {}

        /// <summary>
        /// Adds a new element to the end of the collection
        /// </summary>
        /// <parm name="value">Value to add. </parm>
        void Add(const T& value)
        {
            FCollection<T>::m_actualData.push_back(value);
        }

        /// <summary>
        /// Access an element in the array by index.
        /// </summary>
        /// <param name="index">Index to access. </param>
        /// <returns>The element in the List.</returns>
        /// <exception cref="std::out_of_range">
        /// When accessing anything before or after the elements in the array.
        /// Use GetAt() for a safe version of this Method.
        /// </exception>
        T& operator[](size_t index)
        {
            return FCollection<T>::m_actualData[index];
        }

        /// <summary>
        /// Access an element in the array by index.
        /// </summary>
        /// <param name="index">Index to access. </param>
        /// <returns>The element in the List.</returns>
        /// <exception cref="std::out_of_range">
        /// When accessing anything before or after the elements in the array.
        /// Use GetAt() for a safe version of this Method.
        /// </exception>
        const T& operator[](size_t index) const
        {
            return FCollection<T>::m_actualData[index];
        }

    };
}