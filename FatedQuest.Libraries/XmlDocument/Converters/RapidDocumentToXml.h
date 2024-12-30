#pragma once
#include "../../StoredDocument/AllReferences.h"
#include "../RapidXML.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;

    /// <summary>
    /// Converts a stored document to XMl using RapidXml.
    /// </summary>
    class RapidDocumentToXml : public DocumentToXml
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
        /// <param name="document">Document to add to. </param>
        /// <param name="parentNode">Parent document, used to add nodes. </param>
        /// <param name="currentStoredNode">Current data to pull from. </param>
        void AddNodeToDocument(const std::shared_ptr<RapidXML::XML_Document>& document, const std::shared_ptr<RapidXML::XML_Node>& parentNode, const std::shared_ptr<StoredDocumentNode>& currentStoredNode) const;
    };

}
