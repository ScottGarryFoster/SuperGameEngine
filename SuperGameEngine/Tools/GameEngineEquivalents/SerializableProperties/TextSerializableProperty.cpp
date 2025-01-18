#include "TextSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../../Engine/Structural/Serializable/SerializableParser.h"
#include "../../../Engine/Structural/Serializable/PropertyByType/TextSerializableProperty.h"

#include "../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

TextSerializableProperty::TextSerializableProperty(
    const std::shared_ptr<SuperGameEngine::SerializableParser>& parser, 
    const std::shared_ptr<SuperGameEngine::SerializableProperty>& property)
{
    m_property = property;
    m_value[0] = '\0';
    m_serializableParser = parser;
    if (std::shared_ptr<SuperGameEngine::TextSerializableProperty> textProperty = 
        std::dynamic_pointer_cast<SuperGameEngine::TextSerializableProperty>(m_property))
    {
        m_textSerializableProperty = textProperty;
    }
    else
    {
        Log::Warning("Property is not actually a text property but was created as one. Name: " + property->GetName(),
            "TextSerializableProperty::TextSerializableProperty("
            "std::shared_ptr<SuperGameEngine::SerializableParser>,std::shared_ptr<SuperGameEngine::SerializableProperty>)");
        m_textSerializableProperty = std::make_shared<SuperGameEngine::TextSerializableProperty>();
        m_textSerializableProperty->SetName(property->GetName());
        m_property = m_textSerializableProperty;
    }
}

std::shared_ptr<SuperGameEngine::SerializableProperty> TextSerializableProperty::GetEngineProperty() const
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
    std::string value = m_textSerializableProperty->Load(m_serializableParser, node);
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
