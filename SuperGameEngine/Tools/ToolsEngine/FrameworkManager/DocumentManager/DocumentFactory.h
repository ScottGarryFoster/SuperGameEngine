#pragma once
#include <functional>
#include <memory>
#include <map>

namespace SuperGameTools
{
    struct DocumentCriteria;
    class Document;
    class DocumentMatcher;

    /// <summary>
    /// Provides the ability to create documents.
    /// </summary>
    class DocumentFactory
    {
    public:
        /// <summary>
        /// Register a new document.
        /// </summary>
        /// <param name="matcher">Determines if a document request should match a document type. </param>
        /// <param name="constructor">Construction method. Must have no parameters. </param>
        static void RegisterDocument(const std::shared_ptr<DocumentMatcher>& matcher, const std::function<std::shared_ptr<Document>()>& constructor);

        /// <summary>
        /// Create the document if it matches.
        /// </summary>
        /// <param name="criteria">The criteria to match against. </param>
        /// <returns>A document it matches against or empty if no document matches.  </returns>
        static std::shared_ptr<Document> CreateDocument(const DocumentCriteria& criteria);
    private:

        /// <summary>
        /// Get the map containing the document constructors.
        /// </summary>
        /// <returns>All registered documents. </returns>
        static std::map<std::shared_ptr<DocumentMatcher>, std::function<std::shared_ptr<Document>()>>& GetMap()
        {
            // This is initialized here.
            static std::map<std::shared_ptr<DocumentMatcher>, std::function<std::shared_ptr<Document>()>> map;
            return map;
        }
    };
}

// All documents:     REGISTER_DOCUMENT(DocumentMatcher, CLASS)
// Send in a document matcher and the class.
// The matcher will be tested against the file path and contents (if there are any)
// and if it passes then it will be created.

#define REGISTER_DOCUMENT(TYPE, CLASS) \
    static bool CLASS##_registered = []() { \
        DocumentFactory::RegisterDocument(TYPE, []() { return std::make_shared<CLASS>(); }); \
        return true; \
    }()