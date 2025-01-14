#include "TextSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../../Engine/Structural/Serializable/SerializableParser.h"
#include "../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

TextSerializableProperty::TextSerializableProperty(
    const std::shared_ptr<SerializableParser>& parser, 
    const std::shared_ptr<SerializableProperty>& property)
{
    m_property = property;
    m_value[0] = '\0';
    m_serializableParser = parser;
}

std::shared_ptr<SerializableProperty> TextSerializableProperty::GetEngineProperty() const
{
    return m_property;
}

void TextSerializableProperty::Draw()
{
    if (!m_property)
    {
        return;
    }

    ImGui::Text(m_property->GetName().c_str());
    ImGui::SameLine();
    ImGui::InputText("##name", m_value, IM_ARRAYSIZE(m_value));
}

void TextSerializableProperty::Load(const std::shared_ptr<StoredDocumentNode>& node)
{
    std::string value = m_serializableParser->Parse("default", node);
    size_t written = std::snprintf(m_value, sizeof(m_value), "%s", value.c_str());

    if (written >= sizeof(m_value))
    {
        Log::Error("Text storage too small. Needed: " + std::to_string(written + 1),
            "TextSerializableProperty::Load(std::shared_ptr<StoredDocumentNode>)");
    }
    else if (written < 0 || written > sizeof(m_value))
    {
        Log::Error("Encoding error occurred.",
            "TextSerializableProperty::Load(std::shared_ptr<StoredDocumentNode>)");
    }
}

std::shared_ptr<ModifiableNode> TextSerializableProperty::Save() const
{
    std::string str(m_value);
    return m_serializableParser->Serialize("Serial", str, "default");
}
