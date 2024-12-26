#pragma once
#include <string>
#include "../ModelElements/FunctionModel.h"

namespace SuperGameTools
{
    /// <summary>
    /// A property which is updated by a function.
    /// </summary>
    template <typename ReturnType, typename... Args>
    class FunctionProperty
    {
    public:
        FunctionProperty(const std::string& name)
        {
            m_name = name;
            m_value = {};
            m_function = std::make_shared<FunctionModel<ReturnType, Args...>>();
        }

        FunctionProperty(const std::string& name, const ReturnType& initialValue)
        {
            m_name = name;
            m_value = initialValue;
            m_function = std::make_shared<FunctionModel<ReturnType, Args...>>();
        }

        FunctionProperty(const std::string& name, const ReturnType& initialValue, const std::function<ReturnType(Args... args)>& function)
        {
            m_name = name;
            m_value = initialValue;
            m_function = std::make_shared<FunctionModel<ReturnType, Args...>>();
            m_function->SetFunction(function);
        }

        ~FunctionProperty() = default;

        /// <summary>
        /// Set a new value for the property.
        /// </summary>
        /// <param name="value">New value. </param>
        void SetValue(const ReturnType& value)
        {
            m_value = value;
        }

        /// <summary>
        /// Get the value for the property.
        /// </summary>
        /// <returns>The value for the property. </returns>
        ReturnType GetValue() const
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
        /// Updates the property.
        /// </summary>
        void Update(Args... args)
        {
            m_value = m_function->CallFunction(std::forward<Args>(args)...);
        }

    private:

        /// <summary>
        /// Value for the property.
        /// </summary>
        ReturnType m_value;

        /// <summary>
        /// Name of the property.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Function for the property.
        /// </summary>
        std::shared_ptr<FunctionModel<ReturnType, Args...>> m_function;
    };

}

