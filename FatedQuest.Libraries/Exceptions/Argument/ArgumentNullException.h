#pragma once
#include "ArgumentException.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Argument based exceptions are crafted from this exception.
    /// </summary>
    class ArgumentNullException : public ArgumentException
    {
    public:
        ArgumentNullException(const std::string& message) : ArgumentException(message)
        {
            m_type = "ArgumentNullException";
        }
    };
}
