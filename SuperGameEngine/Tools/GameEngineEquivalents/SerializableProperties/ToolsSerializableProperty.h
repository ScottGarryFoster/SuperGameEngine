#pragma once
#include <memory>

namespace SuperGameEngine
{
    class SerializableProperty;
}

namespace SuperGameTools
{
    /// <summary>
    /// Represents everything to tools need to edit and load serializable properties.
    /// </summary>
    class ToolsSerializableProperty
    {
    public:
        /// <summary>
        /// Gets the engine side property.
        /// </summary>
        /// <returns>The engine side property. </returns>
        virtual std::shared_ptr<SuperGameEngine::SerializableProperty> GetEngineProperty() const = 0;

        /// <summary>
        /// Draw the editable section for this property.
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// Save this property.
        /// </summary>
        /// This is a reminder for the next commit.
        //virtual void Save() = 0;
    };

}

