#pragma once
#include <memory>
#include <string>


namespace SuperGameEngine
{
    class SerializableProperty;
}

namespace FatedQuestLibraries
{
    class Guid;
}

using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ToolsSerializableProperty;

    /// <summary>
    /// A component which represents the data of a game component.
    /// </summary>
    class Component
    {
    public:
        virtual ~Component() = default;

        /// <summary>
        /// The type of the component.
        /// </summary>
        /// <returns>The type of the component. </returns>
        virtual std::string GetType() const = 0;

        /// <summary>
        /// Set new type.
        /// </summary>
        /// <param name="type">New type. </param>
        virtual void SetType(const std::string& type) = 0;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        /// <returns>Properties exposed and serialised in the Tools. </returns>
        virtual std::vector<std::shared_ptr<SerializableProperty>> GetProperties() const = 0;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        /// <returns>Properties exposed and serialised in the Tools. </returns>
        virtual std::vector<std::shared_ptr<ToolsSerializableProperty>> GetToolsProperties() const = 0;
    };
}
