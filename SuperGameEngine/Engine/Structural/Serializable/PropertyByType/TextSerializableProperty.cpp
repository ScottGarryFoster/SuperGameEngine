#include "TextSerializableProperty.h"
#include "../SerializableParser.h"
#include "../../../FatedQuestReferences.h"

using namespace SuperGameEngine;

TextSerializableProperty::TextSerializableProperty()
{
    m_type = SerializableDataType::Text;
    m_defaultValue = {};
}

TextSerializableProperty::TextSerializableProperty(const std::string& defaultValue)
{
    m_type = SerializableDataType::Text;
    m_defaultValue = defaultValue;
}

std::string TextSerializableProperty::GetDefault() const
{
    return m_defaultValue;
}

std::string TextSerializableProperty::Load(
    const std::shared_ptr<SerializableParser>& parser,
    const std::shared_ptr<StoredDocumentNode>& node) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.", 
            "TextSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    if (!node)
    {
        Log::Error("Document Node given was null.",
            "TextSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    return parser->Parse(m_defaultValue, node);
}

std::shared_ptr<ModifiableNode> TextSerializableProperty::Save(
    const std::shared_ptr<SerializableParser>& parser,
    const std::string& valueToSave) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.",
            "TextSerializableProperty::Save"
            "(std::shared_ptr<SerializableParser>,std::string)");
        return {};
    }

    return parser->Serialize(GetName(), valueToSave, GetDefault());
}
