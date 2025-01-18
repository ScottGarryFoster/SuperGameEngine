#pragma once
#include <memory>

#include "../BasicSerializableProperty.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class SerializableParser;

    /// <summary>
    /// A serializable property which stores text.
    /// </summary>
    class TextSerializableProperty : public BasicSerializableProperty
    {
    public:
        TextSerializableProperty();
        TextSerializableProperty(const std::string& defaultValue);

        /// <summary>
        /// The default value for the property.
        /// </summary>
        /// <returns>The default value for the property. </returns>
        virtual std::string GetDefault() const;

        /// <summary>
        /// Loads the property data and parses it to the result.
        /// </summary>
        /// <param name="parser">Parser to use.</param>
        /// <param name="node">
        /// Node to parse data out of,
        /// this should be the exact property node. </param>
        /// <returns>The extracted data. </returns>
        virtual std::string Load(
            const std::shared_ptr<SerializableParser>& parser,
            const std::shared_ptr<StoredDocumentNode>& node) const;

    private:
        /// <summary>
        /// The value to use when nothing is set.
        /// </summary>
        std::string m_defaultValue;
    };
}

