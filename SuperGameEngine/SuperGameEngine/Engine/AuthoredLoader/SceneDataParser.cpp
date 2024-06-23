#include "SceneDataParser.h"
#include "../../LibraryIncludes.h"

using namespace SuperGameEngine;

const std::shared_ptr<ParsedData> SceneDataParser::ParseData(const std::shared_ptr<PrimitiveData> primitiveData)
{
    if (!primitiveData)
    {
        return std::shared_ptr<ParsedData>();
    }

    if (primitiveData->GetName() != m_sceneName)
    {
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    for (const std::shared_ptr<const PrimitiveData>& primitive : primitiveData->GetChildren())
    {
        std::shared_ptr<ParsedData> parsed = AddGameObjects(primitive);
        if (parsed)
        {
            children.push_back(parsed);
        }
    }

    std::string name = primitiveData->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);

    return returnPointer;
}

const std::shared_ptr<ParsedData> SceneDataParser::AddGameObjects(const std::shared_ptr<const PrimitiveData> primitive)
{
    if (primitive->GetName() != m_gameObjectName)
    {
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    for (const std::shared_ptr<const PrimitiveData>& primitive : primitive->GetChildren())
    {
        std::shared_ptr<ParsedData> parsed = AddGameComponents(primitive);
        if (parsed)
        {
            children.push_back(parsed);
        }
    }

    std::string name = primitive->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);

    return returnPointer;
}

const std::shared_ptr<ParsedData> SceneDataParser::AddGameComponents(const std::shared_ptr<const PrimitiveData> primitive)
{
    if (primitive->GetName() != m_gameComponentsName)
    {
        return std::shared_ptr<ParsedData>();
    }

    std::string typeValue = std::string();
    if (!primitive->TryGetProperty("type", typeValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    for (const std::shared_ptr<const PrimitiveData>& primitive : primitive->GetChildren())
    {
        std::shared_ptr<ParsedData> parsed = AddProperties(primitive);
        if (parsed)
        {
            children.push_back(parsed);
        }
    }

    std::string name = primitive->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);
    returnPointer->SetProperty("type", typeValue);

    return returnPointer;
}

const std::shared_ptr<ParsedData> SceneDataParser::AddProperties(const std::shared_ptr<const PrimitiveData> primitive)
{
    if (primitive->GetName() != m_property)
    {
        return std::shared_ptr<ParsedData>();
    }

    std::string typeValue = std::string();
    if (!primitive->TryGetProperty("type", typeValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::shared_ptr<ParsedData> returnPointer = CreatePropertyOfType(primitive, typeValue);
    return returnPointer;
}

const std::shared_ptr<ParsedData> SceneDataParser::CreatePropertyOfType(
    const std::shared_ptr<const PrimitiveData> primitive, const std::string& type)
{
    if (type == "string")
    {
        return CreateStringProperty(primitive);
    }
    if (type == "int")
    {
        return CreateIntProperty(primitive);
    }
    if (type == "float")
    {
        return CreateFloatProperty(primitive);
    }
    if (type == "bool")
    {
        return CreateBoolProperty(primitive);
    }

    return std::shared_ptr<ParsedData>();
}

const std::shared_ptr<ParsedData> SceneDataParser::CreateStringProperty(
    const std::shared_ptr<const PrimitiveData> primitive)
{
    std::string valueValue = std::string();
    if (!primitive->TryGetProperty("value", valueValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::string nameValue = std::string();
    if (!primitive->TryGetProperty("name", nameValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    std::string name = primitive->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);

    returnPointer->SetProperty("type", "string");
    returnPointer->SetProperty("name", nameValue);
    returnPointer->SetProperty("value", valueValue);

    return returnPointer;
}

const std::shared_ptr<ParsedData> SceneDataParser::CreateIntProperty(const std::shared_ptr<const PrimitiveData> primitive)
{
    std::string valueValue = std::string();
    if (!primitive->TryGetProperty("value", valueValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::string nameValue = std::string();
    if (!primitive->TryGetProperty("name", nameValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    int outValue = int();
    if (!IntHelpers::TryParse(valueValue, outValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    std::string name = primitive->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);

    returnPointer->SetProperty("type", "int");
    returnPointer->SetProperty("name", nameValue);

    // We set both the string a int versions
    returnPointer->SetProperty("value", valueValue);
    returnPointer->SetProperty("value", outValue);

    return returnPointer;
}

const std::shared_ptr<ParsedData> SceneDataParser::CreateFloatProperty(const std::shared_ptr<const PrimitiveData> primitive)
{
    std::string valueValue = std::string();
    if (!primitive->TryGetProperty("value", valueValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::string nameValue = std::string();
    if (!primitive->TryGetProperty("name", nameValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    float outValue = float();
    if (!FloatingPointHelpers::TryParse(valueValue, outValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    std::string name = primitive->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);

    returnPointer->SetProperty("type", "float");
    returnPointer->SetProperty("name", nameValue);

    // We set both the string a int versions
    returnPointer->SetProperty("value", valueValue);
    returnPointer->SetProperty("value", outValue);

    return returnPointer;
}

const std::shared_ptr<ParsedData> SuperGameEngine::SceneDataParser::CreateBoolProperty(const std::shared_ptr<const PrimitiveData> primitive)
{
    std::string valueValue = std::string();
    if (!primitive->TryGetProperty("value", valueValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::string nameValue = std::string();
    if (!primitive->TryGetProperty("name", nameValue))
    {
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    bool outValue = false;
    valueValue = StringHelpers::Trim(valueValue);
    StringHelpers::ConvertToLower(valueValue);
    if (valueValue == "true")
    {
        outValue = true;
    }
    else if (valueValue == "false")
    {
        // Do nothing but also not an early out
    }
    else
    {
        // Invalid option
        // Early return for invalid data
        return std::shared_ptr<ParsedData>();
    }

    std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
    std::string name = primitive->GetName();
    std::shared_ptr<ParsedData> returnPointer = std::make_shared<ParsedData>(name, children);

    returnPointer->SetProperty("type", "bool");
    returnPointer->SetProperty("name", nameValue);

    // We set both the string a int versions
    returnPointer->SetProperty("value", valueValue);
    returnPointer->SetBoolProperty("value", outValue);

    return returnPointer;
}
