#pragma once
#include <memory>
#include <string>

#include "DocumentToXml.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class StoredDocument;

    /// <summary>
    /// Uses a simple direct implementation to convert to XML.
    /// </summary>
    class SimpleDocumentToXml : public DocumentToXml
    {
    public:
        /// <summary>
        /// Converts a stored document to xml.
        /// </summary>
        /// <param name="storedDocument">Stored document to convert. </param>
        /// <returns>The stored document in Xml form. </returns>
        virtual std::string ConvertToXml(const std::shared_ptr<StoredDocument>& storedDocument) const override;

    private:
        /// <summary>
        /// Add node to the stored document xml.
        /// </summary>
        /// <param name="currentXml">Current XML to add to. </param>
        /// <param name="currentStoredNode">Current data to pull from. </param>
        /// <param name="numberOfIndents">Number of indents in the file. </param>
        void AddNodeToDocument(std::string& currentXml, const std::shared_ptr<StoredDocumentNode>& currentStoredNode, int numberOfIndents) const;

        /// <summary>
        /// Return the correct characters for the indents.
        /// </summary>
        /// <param name="indents">Number of indents. </param>
        /// <returns>Characters repsenting this number of indents. </returns>
        std::string ReturnIndentsForNumber(int indents) const;

        /// <summary>
        /// Ensures that no characters which mess up xml document are found.
        /// </summary>
        /// <param name="input">Input to clean. </param>
        /// <returns>A clean escaped string. </returns>
        std::string Escape(const std::string& input) const;
    };
}

