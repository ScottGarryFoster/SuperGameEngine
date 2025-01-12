#pragma once
#include "FrameworkManager.h"

namespace SuperGameTools
{
    class ToolsDocumentManager;
    class ToolsSelectionManager;
    class WindowPackage;

    /// <summary>
    /// Manages and holds the larger services for the entire tools engine.
    /// </summary>
    class ToolsFrameworkManager : public FrameworkManager
    {
    public:
        ToolsFrameworkManager(const std::weak_ptr<WindowPackage>& windowsPackage);
        virtual ~ToolsFrameworkManager() override = default;

        /// <summary>
        /// Call once directly after construction.
        /// Required due to reference giving.
        /// </summary>
        void Setup();

        /// <summary>
        /// Manages actions around documents.
        /// </summary>
        /// <returns>Manages actions around documents. </returns>
        virtual std::shared_ptr<DocumentManager> GetDocumentManager() const override;

        /// <summary>
        /// Manages selection across multiple windows.
        /// </summary>
        /// <returns>Manages selection across multiple windows. </returns>
        virtual std::shared_ptr<SelectionManager> GetSelectionManager() const override;

    private:
        /// <summary>
        /// Manages actions around documents.
        /// </summary>
        std::shared_ptr<ToolsDocumentManager> m_documentManager;

        /// <summary>
        /// Manages selection across multiple windows.
        /// </summary>
        std::shared_ptr<ToolsSelectionManager> m_selectionManager;

        /// <summary>
        /// Everything a Window Package might need to run.
        /// </summary>
        /// <remarks>
        /// Must be a weak pointer to avoid circular referencing!
        /// </remarks>
        std::weak_ptr<WindowPackage> m_windowsPackage;
    };
}
