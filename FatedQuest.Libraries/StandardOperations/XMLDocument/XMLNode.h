#pragma once
#include <string>
#include <vector>
#include <memory>
#include "XMLAttribute.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single XML Node within a document.
    /// </summary>
    class XMLNode
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
        virtual const std::vector<std::shared_ptr<XMLAttribute>> Attributes() const = 0;

        /// <summary>
        /// Gets the first child node.
        /// </summary>
        /// <returns>First child or empty pointer. </returns>
        virtual const std::shared_ptr<XMLNode> GetFirstChild() const = 0;

        /// <summary>
        /// Gets the last child node.
        /// </summary>
        /// <returns>Last child or empty pointer. </returns>
        virtual const std::shared_ptr<XMLNode> GetLastChild() const = 0;

        /// <summary>
        /// Gets the node next to this one.
        /// </summary>
        /// <returns>
        /// Node next to this one or empty pointer.
        /// </returns>
        virtual const std::shared_ptr<XMLNode> GetAdjacentNode() const = 0;
    };
}