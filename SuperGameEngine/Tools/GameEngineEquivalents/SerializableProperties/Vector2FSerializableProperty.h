#pragma once
#include <string>

#include "ToolsSerializableProperty.h"
#include "../../../../FatedQuest.Libraries/StandardObjects/Position/FVector2F.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameEngine
{
    class Vector2FSerializableProperty;
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
    class Vector2FSerializableProperty : public ToolsSerializableProperty
    {
    public:
        Vector2FSerializableProperty(
            const std::shared_ptr<SuperGameEngine::SerializableParser>& parser,
            const std::shared_ptr<SuperGameEngine::SerializableProperty>& property);

        /// <summary>
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        /// <returns>Event called when this objects dirty flag has changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnDirtyFlagChanged() const override;

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
        virtual void Load(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node) override;

        /// <summary>
        /// Save this property.
        /// </summary>
        /// <returns>A node which contains the data, this is the property node. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::ModifiableNode> Save() const override;

        /// <summary>
        /// Gets the property this tools property represents.
        /// </summary>
        /// <returns>The property this tools property represents. </returns>
        std::shared_ptr<SuperGameEngine::Vector2FSerializableProperty> GetActualEngineProperty() const;

    private:
        /// <summary>
        /// Event called when this component is dirtied.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onDirtyFlagChanged;

        /// <summary>
        /// True means are dirty.
        /// </summary>
        std::shared_ptr<bool> m_dirty;

        /// <summary>
        /// The engine side property.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableProperty> m_property;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableParser> m_serializableParser;

        /// <summary>
        /// The property this tools property represents.
        /// </summary>
        std::shared_ptr<SuperGameEngine::Vector2FSerializableProperty> m_serializableProperty;

        /// <summary>
        /// The text stored.
        /// </summary>
        int m_defaultTextCapacity = 1024;

        /// <summary>
        /// The current value.
        /// </summary>
        FatedQuestLibraries::FVector2F m_value;

        /// <summary>
        /// Call to update the dirty flag.
        /// </summary>
        /// <param name="newValue">New value for dirty. </param>
        void UpdateDirtyFlag(bool newValue) const;

        /// <summary>
        /// Draw a text box.
        /// </summary>
        /// <param name="label">Label text. Note: No visible label is drawn, this is the ID label. </param>
        /// <param name="value">Value in the box. </param>
        /// <returns>True means changed. </returns>
        bool TextInput(const std::string& label, std::string& value) const;
    };
}


