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
    };
}