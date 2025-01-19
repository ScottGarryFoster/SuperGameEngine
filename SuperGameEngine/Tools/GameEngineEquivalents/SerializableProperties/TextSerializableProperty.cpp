#include "TextSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../../Engine/Structural/Serializable/SerializableParser.h"
#include "../../../Engine/Structural/Serializable/PropertyByType/TextSerializableProperty.h"

#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

TextSerializableProperty::TextSerializableProperty(
    const std::shared_ptr<SuperGameEngine::SerializableParser>& parser, 
    const std::shared_ptr<SuperGameEngine::SerializableProperty>& property)
{
    m_onDirtyFlagChanged = std::make_shared<FEvent>();
    m_dirty = std::make_shared<bool>();
    *m_dirty = false;

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
            "std::shared_ptr<SuperGameEngine::SerializableParser>,"
            "std::shared_ptr<SuperGameEngine::SerializableProperty>)");
        m_textSerializableProperty = std::make_shared<SuperGameEngine::TextSerializableProperty>();
        m_textSerializableProperty->SetName(property->GetName());
        m_property = m_textSerializableProperty;
    }

    if (!SetValueFromString(m_textSerializableProperty->GetDefault()))
    {
        Log::Error("Could not set default data on construct.",
            "TextSerializableProperty::TextSerializableProperty("
            "std::shared_ptr<SuperGameEngine::SerializableParser>,"
            "std::shared_ptr<SuperGameEngine::SerializableProperty>)");
    }
}

std::shared_ptr<FEventSubscriptions> TextSerializableProperty::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
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

    if (*m_dirty)
    {
        ImGui::InputText("##name", m_value, IM_ARRAYSIZE(m_value));
        ImGui::SameLine();
        ImGui::Text("*");
    }
    else
    {
        std::string before = m_value;
        ImGui::InputText("##name", m_value, IM_ARRAYSIZE(m_value));
        std::string after = m_value;

        if (before != after)
        {
            UpdateDirtyFlag(true);
        }
    }

}

void TextSerializableProperty::Load(const std::shared_ptr<StoredDocumentNode>& node)
{
    std::string value = m_textSerializableProperty->Load(m_serializableParser, node);
    if (!SetValueFromString(value))
    {
        Log::Error("Could not set data on load.",
            "TextSerializableProperty::Load(std::shared_ptr<StoredDocumentNode>)");
    }

    UpdateDirtyFlag(false);
}

std::shared_ptr<ModifiableNode> TextSerializableProperty::Save() const
{
    std::string str(m_value);
    UpdateDirtyFlag(false);
    return m_textSerializableProperty->Save(m_serializableParser, str);
}

std::shared_ptr<SuperGameEngine::TextSerializableProperty> TextSerializableProperty::GetTextProperty() const
{
    return m_textSerializableProperty;
}

bool TextSerializableProperty::SetValueFromString(const std::string& newValue)
{
    size_t written = std::snprintf(m_value, sizeof(m_value), "%s", newValue.c_str());

    if (written >= sizeof(m_value))
    {
        Log::Error("Text storage too small. Needed: " + std::to_string(written + 1),
            "TextSerializableProperty::SetValueFromString(std::string)");
        return false;
    }

    if (written < 0 || written > sizeof(m_value))
    {
        Log::Error("Encoding error occurred.",
            "TextSerializableProperty::SetValueFromString(std::string)");
        return false;
    }

    return true;
}

void TextSerializableProperty::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirty)
    {
        *m_dirty = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}