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
    /// Criteria when creating a document from a file.
    /// </summary>
    struct DocumentCriteria
    {
    public:
        /// <summary>
        /// The file path from game package.
        /// </summary>
        std::string FilePath;

        /// <summary>
        /// The document if it could be opened.
        /// </summary>
        std::weak_ptr<StoredDocument> Document;
    };
}

