#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class StoredDocument;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Determines if a document request should match a document type.
    /// </summary>
    class DocumentMatcher
    {
    public:
        /// <summary>
        /// True when the path means this document matches the document.
        /// </summary>
        /// <param name="path">Path for the document. Path from Game Package. </param>
        /// <returns>True when the path means this document matches the document. </returns>
        virtual bool IsDocument(const std::string& path) const = 0;

        /// <summary>
        /// True when the path means this document matches the document.
        /// The contents should also be used for the verification.
        /// Complete loading is not needed.
        /// </summary>
        /// <param name="path">Path for the document. Path from Game Package. </param>
        /// <param name="documentContents">Document contents. </param>
        /// <returns>True when the path means this document matches the document. </returns>
        virtual bool IsDocument(const std::string& path, const std::weak_ptr<StoredDocument>& documentContents) const = 0;
    };
}
