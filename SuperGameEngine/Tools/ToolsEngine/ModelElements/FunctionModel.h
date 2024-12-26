#pragma once
#include <functional>
#include "../../FatedQuestLibraries.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Holds a function.
    /// </summary>
    template <typename ReturnType, typename... Args>
    class FunctionModel
    {
    public:
        FunctionModel()
        {
            m_function = nullptr;
        }

        FunctionModel(const std::function<ReturnType(Args... args)>& function)
        {
            SetFunction(function);
        }

        virtual ~FunctionModel() = default;

        /// <summary>
        /// Sets the function.
        /// </summary>
        /// <param name="function">New function. </param>
        virtual void SetFunction(const std::function<ReturnType(Args... args)>& function)
        {
            m_function = function;
        }

        /// <summary>
        /// Call the function stored.
        /// </summary>
        /// <returns>The answer. </returns>
        virtual ReturnType CallFunction(Args... args) const
        {
            if (m_function)
            {
                return m_function(std::forward<Args>(args)...);
            }

            Log::Error("Function does not exist or was not set.","FunctionModel::CallFunction");
            return {};
        }

    private:
        /// <summary>
        /// Stored function.
        /// </summary>
        std::function<ReturnType(Args... args)> m_function;
    };
}
