#pragma once
#include <string>

#include "ToolsSerializableProperty.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameEngine
{
    class TextureAssetSerializableProperty;
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
    class TextureAssetSerializableProperty : public ToolsSerializableProperty
    {
    public:
        TextureAssetSerializableProperty(
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
        /// Gets the text property this tools property represents.
        /// </summary>
        /// <returns>The text property this tools property represents. </returns>
        std::shared_ptr<SuperGameEngine::TextureAssetSerializableProperty> GetActualEngineProperty() const;

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
        /// The text property this tools property represents.
        /// </summary>
        std::shared_ptr<SuperGameEngine::TextureAssetSerializableProperty> m_serializableProperty;

        /// <summary>
        /// The limit to the size of the string.
        /// </summary>
        const uint32_t m_stringLimit = 1024;

        /// <summary>
        /// The text stored.
        /// </summary>
        char m_value[1024];

        /// <summary>
        /// Set stored value from string.
        /// </summary>
        /// <param name="newValue">New value to set. </param>
        /// <returns>True means could set. </returns>
        bool SetValueFromString(const std::string& newValue);

        /// <summary>
        /// Call to update the dirty flag.
        /// </summary>
        /// <param name="newValue">New value for dirty. </param>
        void UpdateDirtyFlag(bool newValue) const;

        /// <summary>
        /// Add the drag and drop functionality.
        /// </summary>
        /// <param name="xTop">X at the beginning of the element. </param>
        /// <param name="yTop">Y at the beginning of the element. </param>
        /// <param name="xBottom">X at the end of the element. </param>
        /// <param name="yBottom">Y at the end of the element. </param>
        void EnableDropTarget(float xTop, float yTop, float xBottom, float yBottom);
    };
}


