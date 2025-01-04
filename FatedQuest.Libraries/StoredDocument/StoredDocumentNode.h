#pragma once
#include <string>
#include <vector>
#include <memory>

#include "../SharedEnums/CaseSensitivity.h"
#include "../StoredDocument/StoredDocumentAttribute.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single XML Node within a document.
    /// </summary>
    class StoredDocumentNode
    {
    public:
        /// <summary>
        /// Gets the name for the XML Node.
        /// </summary>
        /// <returns>Name of the XML Node. </returns>
        virtual const std::string Name() const = 0;

        /// <summary>
        /// Gets the attributes for this node.
        /// </summary>
        /// <returns>All attributes for this node or an empty list. </returns>
        virtual const std::vector<std::shared_ptr<StoredDocumentAttribute>> Attributes() const = 0;

        /// <summary>
        /// Searches for attribute of the given name.
        /// </summary>
        /// <param name="criteria">Name to search for.</param>
        /// <returns>Attribute if found, or empty if not. </returns>
        virtual const std::shared_ptr<StoredDocumentAttribute> Attribute(const std::string& criteria) const = 0;

        /// <summary>
        /// Searches for attribute of the given name.
        /// </summary>
        /// <param name="criteria">Name to search for.</param>
        /// <param name="caseSensitive">True means any case is acceptable. </param>
        /// <returns>Attribute if found, or empty if not. </returns>
        virtual const std::shared_ptr<StoredDocumentAttribute> Attribute(const std::string& criteria, CaseSensitivity caseSensitive) const = 0;

        /// <summary>
        /// Gets the first child node.
        /// </summary>
        /// <returns>First child or empty pointer. </returns>
        virtual const std::shared_ptr<StoredDocumentNode> GetFirstChild() const = 0;

        /// <summary>
        /// Gets the last child node.
        /// </summary>
        /// <returns>Last child or empty pointer. </returns>
        virtual const std::shared_ptr<StoredDocumentNode> GetLastChild() const = 0;

        /// <summary>
        /// Gets the node next to this one.
        /// </summary>
        /// <returns>
        /// Node next to this one or empty pointer.
        /// </returns>
        virtual const std::shared_ptr<StoredDocumentNode> GetAdjacentNode() const = 0;

        /// <summary>
        /// Get the inner text.
        /// </summary>
        /// <returns>Get the inner text. </returns>
        virtual const std::string Inner() const = 0;
    };
}