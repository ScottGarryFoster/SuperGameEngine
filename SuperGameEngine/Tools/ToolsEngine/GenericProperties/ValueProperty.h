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


