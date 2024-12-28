#pragma once
#include "../SuperXMLDocument/XMLAttribute.h"
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// An XML Attribute created with RapidXML.
    /// </summary>
    class RapidXMLAttribute : public XMLAttribute
    {
    public:
        RapidXMLAttribute();
        RapidXMLAttribute(const std::string& name, const std::string& value);

        /// <summary>
        /// Returns the name of the attribute.
        /// </summary>
        /// <returns>The name of the attribute. </returns>
        virtual const std::string Name() const;

        /// <summary>
        /// Sets name of the attribute.
        /// </summary>
        /// <param name="name">New name of the attribute. </param>
        virtual void SetName(const std::string& name);

        /// <summary>
        /// The value of the attribute.
        /// </summary>
        /// <returns>
        /// The value of the attribute.
        /// Could be empty if nothing is given.
        /// </returns>
        virtual const std::string Value() const;

        /// <summary>
        /// Sets the value for the attribute.
        /// </summary>
        /// <param name="value">New value. </param>
        virtual void SetValue(const std::string& value);

    private:

        /// <summary>
        /// Name of the attribute.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Value of the attribute.
        /// </summary>
        std::string m_value;
    };
}

