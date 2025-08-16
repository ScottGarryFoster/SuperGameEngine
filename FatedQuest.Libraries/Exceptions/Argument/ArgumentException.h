#pragma once
#include "../Exception.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Argument based exceptions are crafted from this exception.
    /// </summary>
    class ArgumentException : public Exception
    {
    public:
        ArgumentException(const std::string& message) : Exception(message)
        {
            m_type = "ArgumentException";
        }
    };
}
