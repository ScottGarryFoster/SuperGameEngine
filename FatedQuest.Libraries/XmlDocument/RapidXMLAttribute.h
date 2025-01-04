#pragma once
#include "../StoredDocument/StoredDocumentAttribute.h"
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// An XML Attribute created with RapidXML.
    /// </summary>
    class RapidXMLAttribute : public StoredDocumentAttribute
    {
    public:
        RapidXMLAttribute();
        RapidXMLAttribute(const std::string& name, const std::string& value);

        /// <summary>
        /// Returns the name of the attribute.
        /// </summary>
        /// <returns>The name of the attribute. </returns>
        virtual const std::string Name() const override;

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
        virtual const std::string Value() const override;

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

        /// <summary>
        /// Ensures attribute does not contain xml escaped strings which cause it to not match plain text.
        /// </summary>
        /// <param name="input">Raw input. </param>
        /// <returns>Input which should match outsider strings. </returns>
        std::string SanitizeAttribute(const std::string& input) const;
    };
}

