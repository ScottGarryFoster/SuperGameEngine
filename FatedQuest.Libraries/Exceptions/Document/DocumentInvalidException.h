#pragma once
#include "DocumentException.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// The contents of the given document were invalid.
    /// </summary>
    class DocumentInvalidException : public DocumentException
    {
    public:
        DocumentInvalidException(const std::string& message) : DocumentException(message)
        {
            m_type = "DocumentInvalidException";
        }
    };
}
