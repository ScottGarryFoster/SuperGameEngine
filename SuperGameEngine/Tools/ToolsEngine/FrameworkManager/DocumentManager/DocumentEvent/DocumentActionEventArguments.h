#pragma once
#include "DocumentEventAction.h"
#include "DocumentEventOpenLevel.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Event arguments used when a document action occurs.
    /// </summary>
    class DocumentActionEventArguments : public FEventArguments
    {
    public:
        DocumentActionEventArguments(const std::shared_ptr<Document>& document, DocumentEventAction action)
        {
            m_document = document;
            m_action = action;
            m_openLevel = DocumentEventOpenLevel::Unknown;
        }
        DocumentActionEventArguments(const std::shared_ptr<Document>& document, DocumentEventAction action, DocumentEventOpenLevel level)
        {
            m_document = document;
            m_action = action;
            m_openLevel = level;
        }

        /// <summary>
        /// What occured to trigger the event.
        /// </summary>
        /// <returns>What occured to trigger the event. </returns>
        DocumentEventAction GetAction() const
        {
            return m_action;
        }

        /// <summary>
        /// How the document suggests being opened.
        /// </summary>
        /// <returns>How the document suggests being opened. </returns>
        /// <remarks>
        /// Only used if the document was opened.
        /// </remarks>
        DocumentEventOpenLevel GetOpenLevel() const
        {
            return m_openLevel;
        }

        /// <summary>
        /// The document for which the action has been caused.
        /// </summary>
        /// <returns>The document for which the action has been caused. </returns>
        std::shared_ptr<Document> GetDocument() const
        {
            return m_document;
        }

    private:

        /// <summary>
        /// The document for which the action has been caused.
        /// </summary>
        std::shared_ptr<Document> m_document;

        /// <summary>
        /// What occured to trigger the event.
        /// </summary>
        DocumentEventAction m_action;

        /// <summary>
        /// How the document suggests being opened.
        /// </summary>
        DocumentEventOpenLevel m_openLevel;
    };
}

