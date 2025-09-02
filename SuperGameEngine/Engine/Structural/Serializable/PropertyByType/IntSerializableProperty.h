#pragma once
#include <memory>

#include "../BasicSerializableProperty.h"

namespace FatedQuestLibraries
{
    class ModifiableNode;
    class StoredDocumentNode;
}

namespace SuperGameEngine
{
    class SerializableParser;

    /// <summary>
    /// A serializable property which stores a whole number.
    /// </summary>
    class IntSerializableProperty : public BasicSerializableProperty
    {
    public:
        IntSerializableProperty();
        IntSerializableProperty(int defaultValue);

        /// <summary>
        /// The default value for the property.
        /// </summary>
        /// <returns>The default value for the property. </returns>
        virtual int GetDefault() const;

        /// <summary>
        /// Loads the property data and parses it to the result.
        /// </summary>
        /// <param name="parser">Parser to use.</param>
        /// <param name="node">
        /// Node to parse data out of,
        /// this should be the exact property node. </param>
        /// <returns>The extracted data. </returns>
        virtual int Load(
            const std::shared_ptr<SerializableParser>& parser,
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node) const;

        /// <summary>
        /// Saves the property data to a format you can write out.
        /// </summary>
        /// <param name="parser">Parser to use. </param>
        /// <param name="valueToSave">Value to save in the property. </param>
        /// <returns>The node to save or empty if there is nothing to save. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::ModifiableNode> Save(
            const std::shared_ptr<SerializableParser>& parser,
            int valueToSave) const;

    private:
        /// <summary>
        /// The value to use when nothing is set.
        /// </summary>
        int m_defaultValue;
    };
}

