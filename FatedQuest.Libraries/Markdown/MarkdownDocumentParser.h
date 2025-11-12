#pragma once
#include "DocumentParser.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Parses markdown documents into meaningful data.
    /// </summary>
    class MarkdownDocumentParser : public DocumentParser
    {
        /// <summary>
        /// Parse the given markdown document to the document elements.
        /// </summary>
        /// <param name="filepath">File path to the document. </param>
        /// <returns>The elements within the document. Could be empty if there was an issue loading the document. </returns>
        virtual std::vector<std::shared_ptr<DocumentElement>> ParseDocument(const std::string& filepath) override;
};
}