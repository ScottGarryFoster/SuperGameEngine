#pragma once
#include "XMLNode.h"

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

    private:
        /// <summary>
        /// Name of the XML Node.
        /// </summary>
        std::string m_name;
    };
}