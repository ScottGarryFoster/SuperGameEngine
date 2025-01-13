#pragma once
#include <memory>
#include <string>
#include <vector>

namespace SuperGameTools
{
    class ToolsSerializableProperty;
}

namespace SuperGameEngine
{
    class SerializableProperty;
}

namespace SuperGameTools
{
    /// <summary>
    /// Loads Serializable properties from components.
    /// </summary>
    class SerializablePropertyLoader
    {
    public:
        /// <summary>
        /// Extracts the properties from the given component.
        /// </summary>
        /// <param name="typeName">Type to extract from. </param>
        /// <returns>Properties on the component. </returns>
        std::vector<std::shared_ptr<SuperGameEngine::SerializableProperty>> EngineFromComponent(const std::string& typeName) const;

        /// <summary>
        /// Extracts the properties from the given component.
        /// </summary>
        /// <param name="typeName">Type to extract from. </param>
        /// <returns>Properties on the component. </returns>
        std::vector<std::shared_ptr<ToolsSerializableProperty>> ToolsFromComponent(const std::string& typeName) const;
    };
}


