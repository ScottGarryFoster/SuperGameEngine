#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class StoredDocument;

    /// <summary>
    /// Converts a Stored Document to XML.
    /// </summary>
    class DocumentToXml
    {
    public:
        /// <summary>
        /// Converts a stored document to xml.
        /// </summary>
        /// <param name="storedDocument">Stored document to convert. </param>
        /// <returns>The stored document in Xml form. </returns>
        virtual std::string ConvertToXml(const std::shared_ptr<StoredDocument>& storedDocument) const = 0;
    };


}