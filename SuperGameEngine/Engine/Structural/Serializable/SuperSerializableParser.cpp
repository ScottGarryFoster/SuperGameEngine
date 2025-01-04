#include "SuperSerializableParser.h"

#include "../../../../FatedQuest.Libraries/StoredDocument/ModifiableNode.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/ModifiableAttribute.h"
#include "../Component/GameComponent.h"

using namespace SuperGameEngine;

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
    // Do not both if value is default.
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
