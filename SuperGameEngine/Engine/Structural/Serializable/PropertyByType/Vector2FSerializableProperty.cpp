#include "Vector2FSerializableProperty.h"
#include "../SerializableParser.h"

#include "../../../../../FatedQuest.Libraries/Logger/Logger/Log.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

Vector2FSerializableProperty::Vector2FSerializableProperty()
{
    m_type = SerializableDataType::Vector2F;
    m_defaultValue = FVector2F(0, 0);
}

Vector2FSerializableProperty::Vector2FSerializableProperty(const FVector2F& defaultValue)
{
    m_type = SerializableDataType::Vector2F;
    m_defaultValue = defaultValue;
}

const FVector2F& Vector2FSerializableProperty::GetDefault() const
{
    return m_defaultValue;
}

FVector2F Vector2FSerializableProperty::Load(
    const std::shared_ptr<SerializableParser>& parser,
    const std::shared_ptr<StoredDocumentNode>& node) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.",
            "Vector2FSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    if (!node)
    {
        Log::Error("Document Node given was null.",
            "Vector2FSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    return parser->Parse(m_defaultValue, node);
}

std::shared_ptr<ModifiableNode> Vector2FSerializableProperty::Save(
    const std::shared_ptr<SerializableParser>& parser, 
    const FVector2F& valueToSave) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.",
            "Vector2FSerializableProperty::Save"
            "(std::shared_ptr<SerializableParser>,std::string)");
        return {};
    }

    return parser->Serialize(GetName(), valueToSave, GetDefault());
}
