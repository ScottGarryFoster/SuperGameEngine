#pragma once
#include <memory>

namespace SuperGameTools
{
    class DocumentManager;
}

namespace SuperGameTools
{
    /// <summary>
    /// Manages and holds the larger services for the entire tools engine.
    /// </summary>
    class FrameworkManager
    {
    public:
        virtual ~FrameworkManager() = default;

        /// <summary>
        /// Manages actions around documents.
        /// </summary>
        /// <returns>Manages actions around documents. </returns>
        virtual std::shared_ptr<DocumentManager> GetDocumentManager() const = 0;
    };
}
