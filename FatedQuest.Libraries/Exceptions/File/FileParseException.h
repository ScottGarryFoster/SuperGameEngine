#pragma once
#include "../Exception.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Thrown when a file is unable to be parsed.
    /// </summary>
    class FileParseException : public Exception
    {
    public:
        FileParseException(const std::string& message) : Exception(message)
        {
            m_type = "FileParseException";
        }
    };
}
