#pragma once

#include "../../Object/Object.h"
#include <vector>
#include <algorithm>
#include <functional>

namespace StandardCLibrary
{
    /// <summary>
    /// Data stored as a set.
    /// </summary>
    template<typename T>
    class FCollection : public Object
    {
    public:
        FCollection()
        {
        }

        /// <summary>
        /// Constructor with a single value.
        /// </summary>
        /// <param name="value">Single value to add. </param>
        FCollection(const T& value)
        {
            m_actualData.push_back(value);
        }

        /// <summary>
        /// Constructor with many values.
        /// </summary>
        /// <param name="values">Many values to add. </param>
        FCollection(const std::vector<T> values)
        {
            for (T value : values)
            {
                m_actualData.push_back(value);
            }
        }

        /// <summary>
        /// Constructor with many values.
        /// Explict copy to recreate the FCollection.
        /// </summary>
        /// <param name="overload">Ignored. Send into explictly call this constructor. </param>
        /// <param name="values">Many values to add. </param>
        FCollection(bool overload, const FCollection<T> values)
        {
            for (T value : values)
            {
                m_actualData.push_back(value);
            }
        }

        /// <summary>
        /// Iterator so that you may use this in foreach loops.
        /// </summary>
        /// <returns>Iterator. </returns>
        auto begin() const
        {
            return m_actualData.begin();
        }

        /// <summary>
        /// Iterator so that you may use this in foreach loops.
        /// </summary>
        /// <returns>Iterator. </returns>
        auto end() const
        {
            return m_actualData.end();
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
        FCollection<T> Where(std::function<bool(const T&)> predicate)
        {
            std::vector<T> filteredComponents;
            for (const auto& component : m_actualData)
            {
                if (predicate(component))
                {
                    filteredComponents.push_back(component);
                }
            }

            FCollection<T> returnCollection(filteredComponents);
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
        FCollection<T> Where(std::function<bool(const T*)> predicate)
        {
            std::vector<T> filteredComponents;
            for (const auto& component : m_actualData)
            {
                if (predicate(component))
                {
                    filteredComponents.push_back(component);
                }
            }

            FCollection<T*> returnCollection(filteredComponents);
            return returnCollection;
        }

        /// <summary>
        /// From the items in the collection extract the given Type.
        /// </summary>
        /// <typeparam name="TResult">Type of the result to extract. </typeparam>
        /// <param name="predicate">
        /// A lamda to take the Type and return the Result.
        /// Imagine it is run upon each element in the collection.
        /// </param>
        /// <returns>A collection of your results. </returns>
        /// <example>
        /// To extract return the actual element you want.
        /// <code>
        ///     FCollection<std::string> selectedSquares = 
        ///         collection.Select<std::string>
        ///         ([](const FString& num){ return num.AsStdString(); });
        /// </code>
        /// You can select an item in say a class to extract them all.
        /// </example>
        template<typename TResult>
        FCollection<TResult> Select(std::function<TResult(const T&)> predicate) const
        {
            std::vector<TResult> selectedItems;
            selectedItems.reserve(m_actualData.size());
            for (const auto& item : m_actualData)
            {
                selectedItems.push_back(predicate(item));
            }

            return FCollection<TResult>(selectedItems);
        }

        /// <summary>
        /// From the items in the collection extract the given Type.
        /// </summary>
        /// <typeparam name="TResult">Type of the result to extract. </typeparam>
        /// <param name="predicate">
        /// A lamda to take the Type and return the Result.
        /// Imagine it is run upon each element in the collection.
        /// </param>
        /// <returns>A collection of your results. </returns>
        /// <example>
        /// To extract return the actual element you want.
        /// <code>
        ///     FCollection<std::string> selectedSquares = 
        ///         collection.Select<std::string>
        ///         ([](const FString* num){ return num->AsStdString(); });
        /// </code>
        /// You can select an item in say a class to extract them all.
        /// </example>
        template<typename TResult>
        FCollection<TResult> Select(std::function<TResult(const T*)> predicate) const
        {
            std::vector<TResult> selectedItems;
            selectedItems.reserve(m_actualData.size());
            for (const auto& item : m_actualData)
            {
                selectedItems.push_back(predicate(item));
            }

            return FCollection<TResult>(selectedItems);
        }

        /// <summary>
        /// Counts all elements in the collection.
        /// </summary>
        /// <returns>The number of elements in the collection. </returns>
        size_t Count()
        {
            return m_actualData.size();
        }

        /// <summary>
        /// Determines if there are any entries in the collection.
        /// </summary>
        /// <returns>True means there are entries.</returns>
        bool Any()
        {
            return m_actualData.size() > 0;
        }

    protected:

        /// <summary>
        /// The actual storage for the data.
        /// </summary>
        std::vector<T> m_actualData;
    };
}
