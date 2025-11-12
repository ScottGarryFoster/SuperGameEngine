#pragma once
#include <memory>
#include <vector>
#include <string>

namespace FatedQuestLibraries
{
    class DocumentElement;

    /// <summary>
    /// Parses documents into meaningful data.
    /// </summary>
    class DocumentParser
    {
        /// <summary>
        /// Parse the given document to the document elements.
        /// </summary>
        /// <param name="filepath">File path to the document. </param>
        /// <returns>The elements within the document. Could be empty if there was an issue loading the document. </returns>
        virtual std::vector<std::shared_ptr<DocumentElement>> ParseDocument(const std::string& filepath) = 0;
    };
}
