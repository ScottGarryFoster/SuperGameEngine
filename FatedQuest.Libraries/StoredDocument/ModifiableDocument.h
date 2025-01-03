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
        /// <remarks>
        /// This is a copy operation and expects the data you would like to exist
        /// to be within this node at the time you give it to the document.
        /// </remarks>
        virtual void SetRootElement(const std::shared_ptr<StoredDocumentNode>& rootDocument);

        /// <summary>
        /// Set the root element from a modifiable node.
        /// </summary>
        /// <param name="rootNode">Root node to update. </param>
        /// <remarks>
        /// This version assumes you have already loaded any data you would like and will not
        /// inspect the modifiable node for data.
        /// </remarks>
        virtual void SetRootElement(const std::shared_ptr<ModifiableNode>& rootNode);

    private:
        /// <summary>
        /// Root element of the document.
        /// </summary>
        std::shared_ptr<ModifiableNode> m_root;
    };


}
