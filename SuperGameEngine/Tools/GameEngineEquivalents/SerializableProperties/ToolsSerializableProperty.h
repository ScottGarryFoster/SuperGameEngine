#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class ModifiableNode;
    class StoredDocumentNode;
}

namespace SuperGameEngine
{
    class SerializableProperty;
}

using namespace FatedQuestLibraries;

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
        /// Load the property from stored data.
        /// </summary>
        /// <param name="node">Node for this property. </param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& node) = 0;

        /// <summary>
        /// Save this property.
        /// </summary>
        /// <returns>A node which contains the data, this is the property node. </returns>
        virtual std::shared_ptr<ModifiableNode> Save() const = 0;
    };

}

