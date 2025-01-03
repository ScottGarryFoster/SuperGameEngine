#pragma once
#include "StoredDocumentNode.h"
#include "../SharedEnums/CaseSensitivity.h"

namespace FatedQuestLibraries
{
    class ModifiableAttribute;

    /// <summary>
    /// A document node which can be modified.
    /// </summary>
    class ModifiableNode : public StoredDocumentNode
    {
    public:
        ModifiableNode();
        virtual ~ModifiableNode() = default;

        /// <summary>
        /// Gets the name for the XML Node.
        /// </summary>
        /// <returns>Name of the XML Node. </returns>
        virtual const std::string Name() const override;

        /// <summary>
        /// Sets the name.
        /// </summary>
        /// <param name="newName">New name to set. </param>
        void SetName(const std::string& newName);

        /// <summary>
        /// Gets the attributes for this node.
        /// </summary>
        /// <returns>All attributes for this node or an empty list. </returns>
        virtual const std::vector<std::shared_ptr<StoredDocumentAttribute>> Attributes() const override;

        /// <summary>
        /// Set the attributes on this node.
        /// </summary>
        /// <param name="newAttributes">New attributes. </param>
        void SetAttributes(const std::vector<std::shared_ptr<StoredDocumentAttribute>>& newAttributes);

        /// <summary>
        /// Searches for attribute of the given name.
        /// </summary>
        /// <param name="criteria">Name to search for.</param>
        /// <returns>Attribute if found, or empty if not. </returns>
        virtual const std::shared_ptr<StoredDocumentAttribute> Attribute(const std::string& criteria) const override;

        /// <summary>
        /// Searches for attribute of the given name.
        /// </summary>
        /// <param name="criteria">Name to search for.</param>
        /// <param name="caseSensitive">True means any case is acceptable. </param>
        /// <returns>Attribute if found, or empty if not. </returns>
        virtual const std::shared_ptr<StoredDocumentAttribute> Attribute(const std::string& criteria, CaseSensitivity caseSensitive) const override;

        /// <summary>
        /// Gets the first child node.
        /// </summary>
        /// <returns>First child or empty pointer. </returns>
        virtual const std::shared_ptr<StoredDocumentNode> GetFirstChild() const override;

        /// <summary>
        /// Set the first child. This is the first node within this one.
        /// </summary>
        /// <param name="firstChild">New first child. </param>
        void SetFirstChild(const std::shared_ptr<StoredDocumentNode>& firstChild);

        /// <summary>
        /// Gets the last child node.
        /// </summary>
        /// <returns>Last child or empty pointer. </returns>
        virtual const std::shared_ptr<StoredDocumentNode> GetLastChild() const override;

        /// <summary>
        /// Set the last child. This is the last child within the node.
        /// </summary>
        /// <param name="lastChild">New Last Child. </param>
        void SetLastChild(const std::shared_ptr<StoredDocumentNode>& lastChild);

        /// <summary>
        /// Gets the node next to this one.
        /// </summary>
        /// <returns>
        /// Node next to this one or empty pointer.
        /// </returns>
        virtual const std::shared_ptr<StoredDocumentNode> GetAdjacentNode() const override;

        /// <summary>
        /// Set the node adjacent to this one. This is not the child but on the same level.
        /// </summary>
        /// <param name="adjacentNode"></param>
        void SetAdjacentNode(const std::shared_ptr<StoredDocumentNode>& adjacentNode);

        /// <summary>
        /// Sets the children of this node.
        /// Will also ensure that each child knows about one another.
        /// </summary>
        /// <param name="allNodes">All children nodes.</param>
        void SetAllChildrenNodes(const std::vector<std::shared_ptr<ModifiableNode>>& allNodes);

        /// <summary>
        /// Get the inner text.
        /// </summary>
        /// <returns>Get the inner text. </returns>
        virtual const std::string Inner() const override;

        /// <summary>
        /// Set the text contained within this node.
        /// </summary>
        /// <param name="innerText">Inner text. </param>
        void SetInnerText(const std::string& innerText);

        /// <summary>
        /// Loads the information from the stored node in this one such
        /// that you can now modify it.
        /// </summary>
        /// <param name="storedNode">Stored node. </param>
        /// <returns>True means parsed. </returns>
        bool Load(const std::shared_ptr<StoredDocumentNode>& storedNode);

    private:
        /// <summary>
        /// Name of the node.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Attributes on the node.
        /// </summary>
        std::vector<std::shared_ptr<ModifiableAttribute>> m_attributes;

        /// <summary>
        /// Precast stored document attributes.
        /// </summary>
        std::vector<std::shared_ptr<StoredDocumentAttribute>> m_attributesStored;

        /// <summary>
        /// First child within this node.
        /// </summary>
        std::shared_ptr<StoredDocumentNode> m_firstChild;

        /// <summary>
        /// Last child within this node.
        /// </summary>
        std::shared_ptr<StoredDocumentNode> m_lastChild;

        /// <summary>
        /// Get the next sibling to this one. This is not the child but on the same level.
        /// </summary>
        std::shared_ptr<StoredDocumentNode> m_adjacentNode;

        /// <summary>
        /// The inner text within this node.
        /// </summary>
        std::string m_innerText;

        /// <summary>
        /// Ensures attribute does not contain xml escaped strings which cause it to not match plain text.
        /// </summary>
        /// <param name="input">Raw input. </param>
        /// <returns>Input which should match outsider strings. </returns>
        std::string SanitizeAttribute(const std::string& input) const;
    };
}

