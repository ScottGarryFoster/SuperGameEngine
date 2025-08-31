#include "SerializablePropertyLoader.h"

#include "../../../Engine/Structural/Component/GameComponent.h"
#include "../../../Engine/Structural/GameObject/ComponentFactory.h"
#include "../SerializableProperties/TextSerializableProperty.h"
#include "../../FatedQuestLibraries.h"
#include "GameEngineEquivalents/SerializableProperties/Vector2FSerializableProperty.h"
#include "Structural/Serializable/PropertyByType/Vector2FSerializableProperty.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

SerializablePropertyLoader::SerializablePropertyLoader(
    const std::shared_ptr<SuperGameEngine::SerializableParser>& parser)
{
    m_serializableParser = parser;
}

std::vector<std::shared_ptr<SuperGameEngine::SerializableProperty>>
    SerializablePropertyLoader::EngineFromComponent(const std::string& typeName) const
{
    auto component = SuperGameEngine::ComponentFactory::CreateComponent(typeName);
    if (component)
    {
        return component->Properties();
    }

    return {};
}

std::vector<std::shared_ptr<ToolsSerializableProperty>> SerializablePropertyLoader::ToolsFromComponent(
    const std::string& typeName) const
{
    auto component = SuperGameEngine::ComponentFactory::CreateComponent(typeName);
    if (!component)
    {
        return {};
    }

    std::vector<std::shared_ptr<ToolsSerializableProperty>> toolsProperties;
    for (const std::shared_ptr<SuperGameEngine::SerializableProperty>& property : component->Properties())
    {
        switch (property->GetType())
        {
        case SuperGameEngine::SerializableDataType::Text:
            toolsProperties.emplace_back(std::make_shared<TextSerializableProperty>
                (m_serializableParser, property));
            break;
        case SuperGameEngine::SerializableDataType::Vector2F:
            toolsProperties.emplace_back(std::make_shared<Vector2FSerializableProperty>
                (m_serializableParser, property));
            break;
        default:
            Log::Error("Could not find a Tools Property for type: " + 
                SuperGameEngine::ESerializableDataType::ToString(property->GetType()),
                "std::vector<std::shared_ptr<ToolsSerializableProperty>> "
                "SerializablePropertyLoader::ToolsFromComponent(std::string) const");
        }
    }

    return toolsProperties;
}
