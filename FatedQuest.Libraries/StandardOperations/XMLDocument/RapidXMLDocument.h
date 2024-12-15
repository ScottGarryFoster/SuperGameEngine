#pragma once
#include "SuperXMLDocument.h"
#include "RapidXMLNode.h"
#include "RapidXML.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Parses document into XML via the Rapid Libraries.
    /// </summary>
    class RapidXMLDocument : public SuperXMLDocument
    {
    public:
        RapidXMLDocument();

        /// <summary>
        /// Loads XML Document from the contents within the file.
        /// </summary>
        /// <param name="path">Absolute file path. </param>
        /// <returns>True means parsed. </returns>
        virtual bool LoadFromFile(const std::string& path) override;

        /// <summary>
        /// Loads XML Document from the file contents.
        /// </summary>
        /// <param name="path">Contents of the XML document. </param>
        /// <returns>True means parsed. </returns>
        virtual bool Load(const std::string& fileContents) override;

        /// <summary>
        /// Gets the root XMLNode for the document.
        /// </summary>
        /// <returns>
        /// If could not parse, then an empty pointer.
        /// If could parse then the root XMLNode.
        /// </returns>
        virtual std::shared_ptr<XMLNode> GetRoot() override;

    private:
        /// <summary>
        /// Parses path to XML.
        /// </summary>
        /// <param name="path">Path to parse. </param>
        /// <param name="didParse">Set during the parinsing. True means parsed. </param>
        /// <returns>XML Document parsed or empty. </returns>
        std::shared_ptr<RapidXML::XML_Document> TryParseXMLDocument(const std::string& xmlContents, bool& didParse);

        /// <summary>
        /// Root node for the document.
        /// </summary>
        std::shared_ptr<RapidXMLNode> m_rootNode;

        /// <summary>
        /// Parses RapidNode into the internal node.
        /// </summary>
        /// <param name="currentNode">Current stage of the node. </param>
        /// <returns>The top level version of the given node. </returns>
        std::shared_ptr<RapidXMLNode> ParseNode(RapidXML::XML_Node* currentNode);
    };
}

