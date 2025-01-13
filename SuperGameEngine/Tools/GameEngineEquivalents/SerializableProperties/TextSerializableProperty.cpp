#include "TextSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

TextSerializableProperty::TextSerializableProperty(const std::shared_ptr<SerializableProperty>& property)
{
    m_property = property;
    m_value[0] = '\0';
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
