#pragma once
#include <vector>

#include "Component.h"

namespace SuperGameEngine
{
    class SerializableParser;
    class SerializableProperty;
}

using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ToolsSerializableProperty;

    /// <summary>
    /// A component which represents the data of a game component.
    /// </summary>
    class ToolsComponent : public Component
    {
    public:
        virtual ~ToolsComponent() override = default;
        ToolsComponent(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser);

        /// <summary>
        /// The type of the component.
        /// </summary>
        /// <returns>The type of the component. </returns>
        virtual std::string GetType() const override;

        /// <summary>
        /// Set new type.
        /// </summary>
        /// <param name="type">New type. </param>
        virtual void SetType(const std::string& type) override;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        /// <returns>Properties exposed and serialised in the Tools. </returns>
        virtual std::vector<std::shared_ptr<SerializableProperty>> GetProperties() const override;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        /// <returns>Properties exposed and serialised in the Tools. </returns>
        virtual std::vector<std::shared_ptr<ToolsSerializableProperty>> GetToolsProperties() const override;

        /// <summary>
        /// Load the component from stored data.
        /// </summary>
        /// <param name="node">Node for this component. </param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& node) override;

        /// <summary>
        /// Save this component.
        /// </summary>
        /// <returns>A node which contains the data, this is the component node. </returns>
        virtual std::shared_ptr<ModifiableNode> Save() const override;

    private:
        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableParser> m_serializableParser;

        /// <summary>
        /// The type of the component.
        /// </summary>
        std::string m_type;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        std::vector<std::shared_ptr<SerializableProperty>> m_serializableProperties;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        std::vector<std::shared_ptr<ToolsSerializableProperty>> m_serializableToolsProperties;
    };
}
