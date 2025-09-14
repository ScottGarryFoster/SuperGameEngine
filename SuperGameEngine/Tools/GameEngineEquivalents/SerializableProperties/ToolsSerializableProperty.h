#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
    class ModifiableNode;
    class StoredDocumentNode;
}

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
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        /// <returns>Event called when this objects dirty flag has changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnDirtyFlagChanged() const = 0;

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
        virtual void Load(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node) = 0;

        /// <summary>
        /// Save this property.
        /// </summary>
        /// <returns>A node which contains the data, this is the property node. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::ModifiableNode> Save() const = 0;
    };

}

