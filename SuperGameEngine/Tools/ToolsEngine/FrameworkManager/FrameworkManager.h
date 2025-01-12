#pragma once
#include <memory>

namespace SuperGameTools
{
    class SelectionManager;
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

        /// <summary>
        /// Manages selection across multiple windows.
        /// </summary>
        /// <returns>Manages selection across multiple windows. </returns>
        virtual std::shared_ptr<SelectionManager> GetSelectionManager() const = 0;
    };
}
