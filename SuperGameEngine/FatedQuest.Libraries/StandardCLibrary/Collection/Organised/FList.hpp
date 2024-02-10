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
        FList(bool overload, const FCollection<T> values) : FCollection<T>(overload, values) {}

        /// <summary>
        /// Adds a new element to the end of the collection
        /// </summary>
        /// <parm name="value">Value to add. </parm>
        void Add(const T& value)
        {
            FCollection<T>::m_actualData.push_back(value);
        }

        /// <summary>
        /// Returns a Collection for which the items all match the predicate.
        /// </summary>
        /// <param name="predicate">Preicate to match against.</param>
        /// <returns>FCollection which matches or one with zero elements. </returns>
        /// <example> 
        /// To use the predicate send in a lambda function returning a bool with the Type.
        /// For instance if the Collection were a set of strings:
        /// <code>
        ///     collection.Where(
        ///         [](const FString& c) { return c.ToLower().AsStdString() == "something"; }
        ///         );
        /// </code>
        /// This would match anything equalling the word 'something'
        /// </example>
        FList<T> Where(std::function<bool(const T&)> predicate)
        {
            FCollection<T> collection = FCollection<T>::Where(predicate);
            FList<T> returnCollection(true, collection);
            return returnCollection;
        }

        /// <summary>
        /// Returns a Collection for which the items all match the predicate.
        /// </summary>
        /// <param name="predicate">Preicate to match against.</param>
        /// <returns>FCollection which matches or one with zero elements. </returns>
        /// <example> 
        /// To use the predicate send in a lambda function returning a bool with the Type.
        /// For instance if the Collection were a set of strings:
        /// <code>
        ///     collection.Where(
        ///         [](const FString* c) { return c->ToLower()->AsStdString() == "something"; }
        ///         );
        /// </code>
        /// This would match anything equalling the word 'something'
        /// </example>
        FList<T> Where(std::function<bool(const T*)> predicate)
        {
            FCollection<T*> collection = FCollection<T*>::Where(predicate);
            FList<T*> returnCollection(true, collection);
            return returnCollection;
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