#pragma once
#include "../Exception.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Thrown upon reading a document such as a StoredDocument type.
    /// </summary>
    class DocumentException : public Exception
    {
    public:
        DocumentException(const std::string& message) : Exception(message)
        {
            m_type = "DocumentException";
        }
    };
}
