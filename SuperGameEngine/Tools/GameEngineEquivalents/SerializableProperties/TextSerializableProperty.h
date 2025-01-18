#pragma once
#include <string>

#include "ToolsSerializableProperty.h"

namespace SuperGameEngine
{
    class TextSerializableProperty;
}

namespace SuperGameEngine
{
    class SerializableParser;
}

namespace SuperGameTools
{
    /// <summary>
    /// Represents text input.
    /// </summary>
    class TextSerializableProperty : public ToolsSerializableProperty
    {
    public:
        TextSerializableProperty(
            const std::shared_ptr<SuperGameEngine::SerializableParser>& parser, 
            const std::shared_ptr<SuperGameEngine::SerializableProperty>& property);

        /// <summary>
        /// Gets the engine side property.
        /// </summary>
        /// <returns>The engine side property. </returns>
        virtual std::shared_ptr<SuperGameEngine::SerializableProperty> GetEngineProperty() const override;

        /// <summary>
        /// Draw the editable section for this property.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Load the property from stored data.
        /// </summary>
        /// <param name="node">Node for this property. </param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& node) override;

        /// <summary>
        /// Save this property.
        /// </summary>
        /// <returns>A node which contains the data, this is the property node. </returns>
        virtual std::shared_ptr<ModifiableNode> Save() const override;

        /// <summary>
        /// Gets the text property this tools property represents.
        /// </summary>
        /// <returns>The text property this tools property represents. </returns>
        std::shared_ptr<SuperGameEngine::TextSerializableProperty> GetTextProperty() const;

    private:
        /// <summary>
        /// The engine side property.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableProperty> m_property;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableParser> m_serializableParser;

        /// <summary>
        /// The text property this tools property represents.
        /// </summary>
        std::shared_ptr<SuperGameEngine::TextSerializableProperty> m_textSerializableProperty;

        /// <summary>
        /// The text stored.
        /// </summary>
        char m_value[1024];
    };
}


