#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    /// <summary>
    /// A class that can be serialized into Text form.
    /// </summary>
    class Serializable
    {
    public:
        virtual ~Serializable() = default;

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) = 0;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() = 0;
    };
}
