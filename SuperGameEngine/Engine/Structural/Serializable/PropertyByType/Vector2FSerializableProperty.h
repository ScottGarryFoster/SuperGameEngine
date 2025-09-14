#pragma once
#include <memory>

#include "../BasicSerializableProperty.h"
#include "../../../../../FatedQuest.Libraries/StandardObjects/Position/FVector2F.h"

namespace FatedQuestLibraries
{
    class ModifiableNode;
    class StoredDocumentNode;
}

namespace SuperGameEngine
{
    class SerializableParser;

    /// <summary>
    /// A serializable property which stores a Vector2F.
    /// </summary>
    class Vector2FSerializableProperty : public BasicSerializableProperty
    {
    public:
        Vector2FSerializableProperty();
        Vector2FSerializableProperty(const FatedQuestLibraries::FVector2F& defaultValue);

        /// <summary>
        /// The default value for the property.
        /// </summary>
        /// <returns>The default value for the property. </returns>
        virtual const FatedQuestLibraries::FVector2F& GetDefault() const;

        /// <summary>
        /// Loads the property data and parses it to the result.
        /// </summary>
        /// <param name="parser">Parser to use.</param>
        /// <param name="node">
        /// Node to parse data out of,
        /// this should be the exact property node. </param>
        /// <returns>The extracted data. </returns>
        virtual FatedQuestLibraries::FVector2F Load(
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
            const FatedQuestLibraries::FVector2F& valueToSave) const;

    private:
        /// <summary>
        /// The value to use when nothing is set.
        /// </summary>
        FatedQuestLibraries::FVector2F m_defaultValue;
    };
}

