#pragma once
#include "StoredDocumentAttribute.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// An attribute for a document which can be modified.
    /// </summary>
    class ModifiableAttribute : public StoredDocumentAttribute
    {
    public:
        ModifiableAttribute();
        ModifiableAttribute(const std::string& name, const std::string& value);
        virtual ~ModifiableAttribute() = default;

        /// <summary>
        /// Returns the name of the attribute.
        /// </summary>
        /// <returns>The name of the attribute. </returns>
        virtual const std::string Name() const override;

        /// <summary>
        /// The value of the attribute.
        /// </summary>
        /// <returns>
        /// The value of the attribute.
        /// Could be empty if nothing is given.
        /// </returns>
        virtual const std::string Value() const override;

        /// <summary>
        /// Sets the name for the attribute.
        /// </summary>
        /// <param name="newName">New name to set. </param>
        void SetName(const std::string& newName);

        /// <summary>
        /// Set the value for the attribute.
        /// </summary>
        /// <param name="newValue">New value to set. </param>
        void SetValue(const std::string& newValue);

    private:
        /// <summary>
        /// Attribute name.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Attribute value.
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
