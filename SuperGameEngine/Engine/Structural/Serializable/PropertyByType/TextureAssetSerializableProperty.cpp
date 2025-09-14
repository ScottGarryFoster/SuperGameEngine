#include "TextureAssetSerializableProperty.h"
#include "../SerializableParser.h"
#include "../../../FatedQuestReferences.h"

using namespace SuperGameEngine;

TextureAssetSerializableProperty::TextureAssetSerializableProperty()
{
    m_type = SerializableDataType::TextureAsset;
    m_defaultValue = {};
}

TextureAssetSerializableProperty::TextureAssetSerializableProperty(const std::string& defaultValue)
{
    m_type = SerializableDataType::TextureAsset;
    m_defaultValue = defaultValue;
}

std::string TextureAssetSerializableProperty::GetDefault() const
{
    return m_defaultValue;
}

std::string TextureAssetSerializableProperty::Load(
    const std::shared_ptr<SerializableParser>& parser,
    const std::shared_ptr<StoredDocumentNode>& node) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.", 
            "TextureAssetSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    if (!node)
    {
        Log::Error("Document Node given was null.",
            "TextureAssetSerializableProperty::Load"
            "(std::shared_ptr<SerializableParser>,std::shared_ptr<StoredDocumentNode>)");
        return m_defaultValue;
    }

    return parser->Parse(m_defaultValue, node);
}

std::shared_ptr<ModifiableNode> TextureAssetSerializableProperty::Save(
    const std::shared_ptr<SerializableParser>& parser,
    const std::string& valueToSave) const
{
    if (!parser)
    {
        Log::Error("Parser given was null.",
            "TextureAssetSerializableProperty::Save"
            "(std::shared_ptr<SerializableParser>,std::string)");
        return {};
    }

    return parser->Serialize(GetName(), valueToSave, GetDefault());
}
