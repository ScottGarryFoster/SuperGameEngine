#pragma once
#include <string>


namespace SuperGameTools
{
    /// <summary>
    /// Holds a property as part of a larger View/Model.
    /// </summary>
    template <typename ValueType>
    class ValueProperty
    {
    public:
        ValueProperty(const std::string& name)
        {
            m_name = name;
            m_value = {};
        }

        ValueProperty(const std::string& name, const ValueType& initialValue)
        {
            m_name = name;
            m_value = initialValue;
        }

        ~ValueProperty() = default;

        /// <summary>
        /// Set a new value for the property.
        /// </summary>
        /// <param name="value">New value. </param>
        void SetValue(const ValueType& value)
        {
            m_value = value;
        }

        /// <summary>
        /// Get the value for the property.
        /// </summary>
        /// <returns>The value for the property. </returns>
        ValueType GetValue() const
        {
            return m_value;
        }

        /// <summary>
        /// Name for the property.
        /// </summary>
        /// <returns>Name for the property. </returns>
        std::string GetName() const
        {
            return m_name;
        }

        /// <summary>
        /// Removes element from a type for which that makes sense.
        /// </summary>
        /// <typeparam name="Predicate">Predicate as to which to erase. </typeparam>
        /// <param name="predicate">Predicate as to which to erase.  </param>
        /// <remarks>Only use for types which use erase_if </remarks>
        template <typename Predicate>
        requires FatedQuestLibraries::Erasable<ValueType>
        void Remove(const Predicate& predicate)
        {
            std::erase_if(m_value, predicate);
        }

    private:

        /// <summary>
        /// Value for the property.
        /// </summary>
        ValueType m_value;

        /// <summary>
        /// Name of the property.
        /// </summary>
        std::string m_name;
    };
}


