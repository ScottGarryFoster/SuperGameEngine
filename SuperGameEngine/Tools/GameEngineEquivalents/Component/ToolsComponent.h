#pragma once
#include <vector>

#include "Component.h"

namespace SuperGameEngine
{
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

    private:
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
