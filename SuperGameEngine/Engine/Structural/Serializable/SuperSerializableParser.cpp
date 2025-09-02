#include "SuperSerializableParser.h"

#include "../../FatedQuestReferences.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/ModifiableNode.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/ModifiableAttribute.h"
#include "../Component/GameComponent.h"


using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

std::shared_ptr<ModifiableNode> SuperSerializableParser::Serialize(
    const std::shared_ptr<GameComponent>& gameComponent) const
{
    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Component");

    auto componentAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Type", gameComponent->TypeName());
        componentAttributes.emplace_back(attribute);
    }

    // TODO: Add Guids to Components as we will need them for object resolve.

    node->SetAttributes(componentAttributes);

    return node;
}

std::shared_ptr<ModifiableNode> SuperSerializableParser::Serialize(
    const std::string& name,
    const std::string& value,
    const std::string& defaultValue) const
{
    // Do not bother if value is default.
    if (value == defaultValue)
    {
        return {};
    }

    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Property");

    auto componentAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Name", name);
        componentAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Value", value);
        componentAttributes.emplace_back(attribute);
    }

    node->SetAttributes(componentAttributes);

    return node;
}

std::string SuperSerializableParser::ParseFromParent(
    const std::string& name,
    const std::string& defaultValue, 
    const std::shared_ptr<StoredDocumentNode>& parentOfProperties) const
{
    for (std::shared_ptr<StoredDocumentNode> child = parentOfProperties->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        if (child->Name() != "Property")
        {
            continue;
        }

        std::shared_ptr<StoredDocumentAttribute> nameAttribute = child->Attribute("Name", CaseSensitivity::IgnoreCase);
        if (!nameAttribute)
        {
            continue;
        }

        if (nameAttribute->Value() != name)
        {
            continue;
        }

        return Parse(defaultValue, child);
    }

    return defaultValue;
}

std::string SuperSerializableParser::Parse(
    const std::string& defaultValue,
    const std::shared_ptr<StoredDocumentNode>& data) const
{
    std::shared_ptr<StoredDocumentAttribute> valueAttribute = data->Attribute("Value", CaseSensitivity::IgnoreCase);
    if (!valueAttribute)
    {
        return defaultValue;
    }

    return valueAttribute->Value();
}

std::shared_ptr<ModifiableNode> SuperSerializableParser::Serialize(
    const std::string& name,
    int value, 
    int defaultValue) const
{
    // Do not bother if value is default.
    if (value == defaultValue)
    {
        return {};
    }

    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Property");

    auto componentAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Name", name);
        componentAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Value", std::to_string(value));
        componentAttributes.emplace_back(attribute);
    }

    node->SetAttributes(componentAttributes);

    return node;
}

int SuperSerializableParser::ParseFromParent(
    const std::string& name, 
    int defaultValue,
    const std::shared_ptr<StoredDocumentNode>& parentOfProperties) const
{
    for (std::shared_ptr<StoredDocumentNode> child = parentOfProperties->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        if (child->Name() != "Property")
        {
            continue;
        }

        std::shared_ptr<StoredDocumentAttribute> nameAttribute = child->Attribute("Name", CaseSensitivity::IgnoreCase);
        if (!nameAttribute)
        {
            continue;
        }

        if (nameAttribute->Value() != name)
        {
            continue;
        }

        return Parse(defaultValue, child);
    }

    return defaultValue;
}

int SuperSerializableParser::Parse(
    int defaultValue,
    const std::shared_ptr<StoredDocumentNode>& data) const
{
    std::shared_ptr<StoredDocumentAttribute> valueAttribute = data->Attribute("Value", CaseSensitivity::IgnoreCase);
    if (!valueAttribute)
    {
        return defaultValue;
    }

    int outValue = 0;
    if (IntHelpers::TryParse(valueAttribute->Value(), outValue))
    {
        return outValue;
    }

    return defaultValue;
}

std::shared_ptr<ModifiableNode> SuperSerializableParser::Serialize(
    const std::string& name,
    const FVector2F& value, 
    const FVector2F& defaultValue) const
{
    // Do not bother if value is default.
    if (value == defaultValue)
    {
        return {};
    }

    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Property");

    auto componentAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Name", name);
        componentAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("X", FloatingPointHelpers::RemoveUnneededZeros(value.GetX()));
        componentAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Y", FloatingPointHelpers::RemoveUnneededZeros(value.GetY()));
        componentAttributes.emplace_back(attribute);
    }

    node->SetAttributes(componentAttributes);

    return node;
}

FVector2F SuperSerializableParser::ParseFromParent(
    const std::string& name,
    const FVector2F& defaultValue,
    const std::shared_ptr<StoredDocumentNode>& parentOfProperties) const
{
    for (std::shared_ptr<StoredDocumentNode> child = parentOfProperties->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        if (child->Name() != "Property")
        {
            continue;
        }

        std::shared_ptr<StoredDocumentAttribute> nameAttribute = child->Attribute("Name", CaseSensitivity::IgnoreCase);
        if (!nameAttribute)
        {
            continue;
        }

        if (nameAttribute->Value() != name)
        {
            continue;
        }

        return Parse(defaultValue, child);
    }

    return defaultValue;
}

FVector2F SuperSerializableParser::Parse(
    const FVector2F& defaultValue,
    const std::shared_ptr<StoredDocumentNode>& data) const
{
    const std::string methodName = "SuperSerializableParser::Parse(const FVector2F&,const std::shared_ptr<StoredDocumentNode>&)";
    FVector2F returnVector;
    {
        std::shared_ptr<StoredDocumentAttribute> valueAttribute = data->Attribute("X", CaseSensitivity::IgnoreCase);
        if (!valueAttribute)
        {
            Log::Error("X value not found in Vector2F property.", methodName);
            return defaultValue;
        }

        float value = 0;
        if (FloatingPointHelpers::TryParse(valueAttribute->Value(), value))
        {
            returnVector.SetX(value);
        }
        else
        {
            Log::Error("Could not parse X value in Vector2F. Value: " + valueAttribute->Value(), methodName);
            return defaultValue;
        }
    }

    {
        std::shared_ptr<StoredDocumentAttribute> valueAttribute = data->Attribute("Y", CaseSensitivity::IgnoreCase);
        if (!valueAttribute)
        {
            Log::Error("Y value not found in Vector2F property.", methodName);
            return defaultValue;
        }

        float value = 0;
        if (FloatingPointHelpers::TryParse(valueAttribute->Value(), value))
        {
            Log::Error("Could not parse Y value in Vector2F. Value: " + valueAttribute->Value(), methodName);
            returnVector.SetY(value);
        }
        else
        {
            return defaultValue;
        }
    }

    return returnVector;
}
