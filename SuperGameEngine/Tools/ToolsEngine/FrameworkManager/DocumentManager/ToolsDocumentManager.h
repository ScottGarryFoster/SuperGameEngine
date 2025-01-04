#pragma once
#include <memory>
#include <string>

#include "DocumentManager.h"
#include "../../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameTools
{
    enum class DocumentEventOpenLevel;
    class FileDialog;
    class WindowPackage;
}

namespace SuperGameTools
{
    /// <summary>
    /// Manages actions around documents.
    /// </summary>
    class ToolsDocumentManager : public DocumentManager, public FEventObserver
    {
    public:
        ToolsDocumentManager(const std::weak_ptr<WindowPackage>& windowsPackage);
        virtual ~ToolsDocumentManager() override = default;

        /// <summary>
        /// Called once after all framework objects are created.
        /// </summary>
        void Setup();

        /// <summary>
        /// Subscribe to event when any document action occurs.
        /// See DocumentActionEventArguments.
        /// </summary>
        /// <returns>Subscribe to event when any document action occurs. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnDocumentAction() const override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;

    private:
        /// <summary>
        /// Access to other elements of Framework manager.
        /// </summary>
        std::weak_ptr<WindowPackage> m_windowsPackage;

        /// <summary>
        /// Occurs when a document action takes place.
        /// See DocumentActionEventArguments.
        /// </summary>
        std::shared_ptr<FEvent> m_onDocumentAction;

        /// <summary>
        /// Allows you to open a file dialog.
        /// </summary>
        std::shared_ptr<FileDialog> m_fileDialog;

        /// <summary>
        /// Full path to products.
        /// Used to make paths opened relative.
        /// </summary>
        std::string m_productsPath;

        /// <summary>
        /// Open a new file.
        /// </summary>
        /// <param name="level">How the document suggests being opened. </param>
        void OpenFile(DocumentEventOpenLevel level);
    };
}

