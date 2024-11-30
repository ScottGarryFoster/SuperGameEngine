#pragma once
#include <string>
#include <memory>
#include "XMLNode.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Parses and organises XML Documents.
    /// </summary>
    /// <remark>
    /// This is called SuperXMLDocument because of a name conflict.
    /// </remark>
    class SuperXMLDocument
    {
    public:
        /// <summary>
        /// Loads XML Document from the contents within the file.
        /// </summary>
        /// <param name="path">Absolute file path. </param>
        /// <returns>True means parsed. </returns>
        virtual bool LoadFromFile(const std::string& path) = 0;

        /// <summary>
        /// Loads XML Document from the file contents.
        /// </summary>
        /// <param name="path">Contents of the XML document. </param>
        /// <returns>True means parsed. </returns>
        virtual bool Load(const std::string& fileContents) = 0;

        /// <summary>
        /// Gets the root XMLNode for the document.
        /// </summary>
        /// <returns>
        /// If could not parse, then an empty pointer.
        /// If could parse then the root XMLNode.
        /// </returns>
        virtual std::shared_ptr<XMLNode> GetRoot() = 0;
    };
}