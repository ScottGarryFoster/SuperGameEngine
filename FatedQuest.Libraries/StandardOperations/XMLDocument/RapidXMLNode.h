#pragma once
#include "XMLNode.h"
#include <memory>
#include "RapidXMLAttribute.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single XML Node within a document.
    /// </summary>
    class RapidXMLNode : public XMLNode
    {
    public:
        RapidXMLNode();

        /// <summary>
        /// Gets the name for the XML Node.
        /// </summary>
        /// <returns>Name of the XML Node. </returns>
        virtual const std::string Name() const override;

        /// <summary>
        /// Sets the name of the XML Node.
        /// </summary>
        /// <param name="name">New name for the XML Node. </param>
        virtual void SetName(const std::string& name);

        /// <summary>
        /// Gets the attributes for this node.
        /// </summary>
        /// <returns>All attributes for this node or an empty list. </returns>
        virtual const std::vector<std::shared_ptr<XMLAttribute>> Attributes() const;

        /// <summary>
        /// Searches for attribute of the given name.
        /// </summary>
        /// <param name="criteria">Name to search for.</param>
        /// <returns>Attribute if found, or empty if not. </returns>
        virtual const std::shared_ptr<XMLAttribute> Attribute(const std::string& criteria) const;

        /// <summary>
        /// Searches for attribute of the given name.
        /// </summary>
        /// <param name="criteria">Name to search for.</param>
        /// <param name="caseSensitive">True means any case is acceptable. </param>
        /// <returns>Attribute if found, or empty if not. </returns>
        virtual const std::shared_ptr<XMLAttribute> Attribute(const std::string& criteria, bool caseSensitive) const;

        /// <summary>
        /// Sets attributes on the Node.
        /// </summary>
        /// <param name="attributes">Attributes to update. Will override not add. </param>
        virtual void SetAttributes(std::vector<std::shared_ptr<XMLAttribute>> attributes);

        /// <summary>
        /// Gets the first child node.
        /// </summary>
        /// <returns>First child or empty pointer. </returns>
        virtual const std::shared_ptr<XMLNode> GetFirstChild() const override;

        /// <summary>
        /// Give the XMLNode it's first child.
        /// </summary>
        /// <param name="child">First child within this node. </param>
        virtual void GiveFirstChild(std::shared_ptr<XMLNode> child);

        /// <summary>
        /// Gets the last child node.
        /// </summary>
        /// <returns>Last child or empty pointer. </returns>
        virtual const std::shared_ptr<XMLNode> GetLastChild() const override;

        /// <summary>
        /// Give the XMLNode it's last child.
        /// </summary>
        /// <param name="child">Last child within this node. </param>
        virtual void GiveLastChild(std::shared_ptr<XMLNode> child);

        /// <summary>
        /// Gets the node next to this one.
        /// </summary>
        /// <returns>
        /// Node next to this one or empty pointer.
        /// </returns>
        virtual const std::shared_ptr<XMLNode> GetAdjacentNode() const override;

        /// <summary>
        /// Give the node next to this one.
        /// </summary>
        /// <param name="next">The next node to this one. </param>
        virtual void GiveAdjacentNode(std::shared_ptr<XMLNode> next);

    private:
        /// <summary>
        /// Name of the XML Node.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Attributes
        /// </summary>
        std::vector<std::shared_ptr<XMLAttribute>> m_attributes;

        /// <summary>
        /// The first direct child of this node.
        /// </summary>
        std::shared_ptr<XMLNode> m_firstChild;

        /// <summary>
        /// The last direct child of this node.
        /// </summary>
        std::shared_ptr<XMLNode> m_lastChild;

        /// <summary>
        /// The child next to this one.
        /// </summary>
        std::shared_ptr<XMLNode> m_nextChild;
    };
}