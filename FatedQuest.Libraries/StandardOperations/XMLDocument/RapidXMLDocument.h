#pragma once
#include "XMLDocument.h"
#include "RapidXML.h"
#include "RapidXMLNode.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Parses document into XML via the Rapid Libraries.
    /// </summary>
    class RapidXMLDocument : public XMLDocument
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
        /// <returns>XML Document or Nullptr if could not parse. </returns>
        RapidXML::XMLDocument* TryParseXMLDocument(const std::string& path);

        /// <summary>
        /// Root node for the document.
        /// </summary>
        std::shared_ptr<RapidXMLNode> m_rootNode;
    };
}

