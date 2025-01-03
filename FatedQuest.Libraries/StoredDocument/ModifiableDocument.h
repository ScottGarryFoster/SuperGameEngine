#pragma once
#include "StoredDocument.h"

namespace FatedQuestLibraries
{
    class ModifiableNode;

    /// <summary>
    /// A modifiable version of a stored document.
    /// </summary>
    class ModifiableDocument : public StoredDocument
    {
    public:
        /// <summary>
        /// Loads XML Document from the contents within the file.
        /// </summary>
        /// <param name="path">Absolute file path. </param>
        /// <returns>True means parsed. </returns>
        virtual bool LoadFromFile(const std::string& path) override;

        /// <summary>
        /// Loads XML Document from the file contents.
        /// </summary>
        /// <param name="fileContents">Contents of the XML document. </param>
        /// <returns>True means parsed. </returns>
        virtual bool Load(const std::string& fileContents) override;

        /// <summary>
        /// Loads the information from the stored document in this one such
        /// that you can now modify it.
        /// </summary>
        /// <param name="storedDocument">Stored document. </param>
        /// <returns>True means parsed. </returns>
        bool Load(const std::shared_ptr<StoredDocument>& storedDocument);

        /// <summary>
        /// Gets the root StoredDocumentNode for the document.
        /// </summary>
        /// <returns>
        /// If could not parse, then an empty pointer.
        /// If could parse then the root StoredDocumentNode.
        /// </returns>
        virtual std::shared_ptr<StoredDocumentNode> GetRoot() override;

        /// <summary>
        /// Gets the root StoredDocumentNode for the document.
        /// </summary>
        /// <returns>
        /// If could not parse, then an empty pointer.
        /// If could parse then the root StoredDocumentNode.
        /// </returns>
        virtual std::shared_ptr<ModifiableNode> GetModifiableRoot();

        /// <summary>
        /// Set the root element of the document.
        /// </summary>
        /// <param name="rootDocument">New root element. </param>
        virtual void SetRootElement(const std::shared_ptr<StoredDocumentNode>& rootDocument);

    private:
        /// <summary>
        /// Root element of the document.
        /// </summary>
        std::shared_ptr<ModifiableNode> m_root;
    };


}
