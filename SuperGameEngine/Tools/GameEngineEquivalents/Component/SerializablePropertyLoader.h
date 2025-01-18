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
    class SerializableParser;
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
        SerializablePropertyLoader(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser);

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

    private:
        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableParser> m_serializableParser;
    };
}


