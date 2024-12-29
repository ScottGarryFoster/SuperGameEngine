#pragma once
#include <string>
#include <vector>
#include <memory>
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
        virtual const std::shared_ptr<StoredDocumentAttribute> Attribute(const std::string& criteria, bool caseSensitive) const = 0;

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
        /// Give the XMLNode it's first child.
        /// </summary>
        /// <param name="child">First child within this node. </param>
        virtual void GiveFirstChild(std::shared_ptr<StoredDocumentNode> child) = 0;

        /// <summary>
        /// Give the XMLNode it's last child.
        /// </summary>
        /// <param name="child">Last child within this node. </param>
        virtual void GiveLastChild(std::shared_ptr<StoredDocumentNode> child) = 0;

        /// <summary>
        /// Give the node next to this one.
        /// </summary>
        /// <param name="next">The next node to this one. </param>
        virtual void GiveAdjacentNode(std::shared_ptr<StoredDocumentNode> next) = 0;

        /// <summary>
        /// Get the inner text.
        /// </summary>
        /// <returns>Get the inner text. </returns>
        virtual const std::string Inner() const = 0;

        /// <summary>
        /// Adds an attribute.
        /// Will fail if an attribute of exactly the same name is added.
        /// </summary>
        /// <param name="attribute">New attribute. </param>
        /// <returns>True means added. </returns>
        virtual bool AddAttribute(const std::shared_ptr<StoredDocumentAttribute>& attribute) = 0;

        /// <summary>
        /// Remove Attribute by name.
        /// Will fail if attribute does not exist.
        /// </summary>
        /// <param name="attributeName">Attribute to remove. </param>
        /// <returns>True means removed. </returns>
        virtual bool RemoveAttribute(const std::string& attributeName) = 0;
    };
}