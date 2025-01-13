#pragma once
#include <string>

#include "ToolsSerializableProperty.h"

namespace SuperGameTools
{
    /// <summary>
    /// Represents text input.
    /// </summary>
    class TextSerializableProperty : public ToolsSerializableProperty
    {
    public:
        TextSerializableProperty(const std::shared_ptr<SuperGameEngine::SerializableProperty>& property);

        /// <summary>
        /// Gets the engine side property.
        /// </summary>
        /// <returns>The engine side property. </returns>
        virtual std::shared_ptr<SuperGameEngine::SerializableProperty> GetEngineProperty() const override;

        /// <summary>
        /// Draw the editable section for this property.
        /// </summary>
        virtual void Draw() override;

    private:
        /// <summary>
        /// The engine side property.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableProperty> m_property;

        /// <summary>
        /// The text stored.
        /// </summary>
        char m_value[1024];
    };
}


