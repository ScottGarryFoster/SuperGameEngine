#pragma once
#include <vector>
#include <algorithm>
#include <functional>

namespace StandardCLibrary
{
    /// <summary>
    /// Data stored as a set.
    /// </summary>
    template<typename T>
    class FCollection
    {
    public:
        /// <summary>
        /// Constructor with a single value.
        /// </summary>
        /// <param name="value">Single value to add</param>
        FCollection(const T& value)
        {
            m_actualData.push_back(value);
        }

        /// <summary>
        /// Constructor with many values.
        /// </summary>
        /// <param name="values">Many values to add.</param>
        FCollection(const std::vector<T> values)
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

    protected:

        /// <summary>
        /// The actual storage for the data.
        /// </summary>
        std::vector<T> m_actualData;
    };
}
