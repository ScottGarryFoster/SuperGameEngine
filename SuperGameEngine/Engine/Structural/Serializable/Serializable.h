#pragma once
#include <memory>

#include "SerializableProperty.h"

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

        /// <summary>
        /// Get all properties which can be authored.
        /// </summary>
        /// <returns>All author-able properties. </returns>
        /// <remarks>
        /// This should be able to be called after construction of the component.
        /// </remarks>
        virtual std::vector<std::shared_ptr<SerializableProperty>> Properties() const = 0;
    };
}
