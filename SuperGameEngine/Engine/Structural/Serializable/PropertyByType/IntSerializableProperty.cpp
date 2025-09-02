#include "IntSerializableProperty.h"
#include "../SerializableParser.h"
#include "../../../FatedQuestReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

IntSerializableProperty::IntSerializableProperty()
{
    m_type = SerializableDataType::Int;
    m_defaultValue = 0;
}

IntSerializableProperty::IntSerializableProperty(int defaultValue)
{
    m_type = SerializableDataType::Int;
    m_defaultValue = defaultValue;
}

int IntSerializableProperty::GetDefault() const
{
    return m_defaultValue;
}

int IntSerializableProperty::Load(
    const std::shared_ptr<SerializableParser>& parser,
    const std::shared_ptr<StoredDocumentNode>& node) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.",
            "IntSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    if (!node)
    {
        Log::Error("Document Node given was null.",
            "IntSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    return parser->Parse(m_defaultValue, node);
}

std::shared_ptr<ModifiableNode> IntSerializableProperty::Save(
    const std::shared_ptr<SerializableParser>& parser, 
    int valueToSave) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.",
            "IntSerializableProperty::Save"
            "(std::shared_ptr<SerializableParser>,int)");
        return {};
    }

    return parser->Serialize(GetName(), valueToSave, GetDefault());
}
