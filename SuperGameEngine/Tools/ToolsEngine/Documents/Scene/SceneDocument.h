#pragma once
#include "../../FrameworkManager/DocumentManager/ToolsDocument.h"
#include "../../FrameworkManager/DocumentManager/DocumentFactory.h"
#include "../../FrameworkManager/DocumentManager/DocumentMatcher.h"

namespace FatedQuestLibraries
{
    class ModifiableDocument;
}

namespace SuperGameTools
{
    /// <summary>
    /// A scene as a document.
    /// </summary>
    class SceneDocument : public ToolsDocument, public DocumentMatcher
    {
    public:
        virtual ~SceneDocument() override = default;

        /// <summary>
        /// Loads the document.
        /// </summary>
        /// <returns>True means loaded. </returns>
        virtual bool Load() override;

        /// <summary>
        /// Saves the document.
        /// </summary>
        /// <returns>True means saved. </returns>
        virtual bool Save() override;

        /// <summary>
        /// True when the path means this document matches the document.
        /// </summary>
        /// <param name="path">Path for the document. Path from Game Package. </param>
        /// <returns>True when the path means this document matches the document. </returns>
        virtual bool IsDocument(const std::string& path) const override;

        /// <summary>
        /// True when the path means this document matches the document.
        /// The contents should also be used for the verification.
        /// Complete loading is not needed.
        /// </summary>
        /// <param name="path">Path for the document. Path from Game Package. </param>
        /// <param name="documentContents">Document contents. </param>
        /// <returns>True when the path means this document matches the document. </returns>
        virtual bool IsDocument(const std::string& path, const std::weak_ptr<StoredDocument>& documentContents) const override;

        /// <summary>
        /// Get the actual stored document.
        /// </summary>
        /// <returns>The actual stored document. </returns>
        std::shared_ptr<ModifiableDocument> GetDocument() const;

    private:
        /// <summary>
        /// Actual document.
        /// </summary>
        std::shared_ptr<ModifiableDocument> m_storedDocument;
    };

    REGISTER_DOCUMENT(std::make_shared<SceneDocument>(), SceneDocument);
}


