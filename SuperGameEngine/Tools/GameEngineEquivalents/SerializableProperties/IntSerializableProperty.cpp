#include "IntSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../../Engine/Structural/Serializable/SerializableParser.h"
#include "../../../Engine/Structural/Serializable/PropertyByType/IntSerializableProperty.h"

#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;


IntSerializableProperty::IntSerializableProperty(
    const std::shared_ptr<SuperGameEngine::SerializableParser>& parser,
    const std::shared_ptr<SuperGameEngine::SerializableProperty>& property)
{
    m_onDirtyFlagChanged = std::make_shared<FEvent>();
    m_dirty = std::make_shared<bool>();
    *m_dirty = false;

    m_property = property;

    m_serializableParser = parser;
    if (std::shared_ptr<SuperGameEngine::IntSerializableProperty> textProperty =
        std::dynamic_pointer_cast<SuperGameEngine::IntSerializableProperty>(m_property))
    {
        m_serializableProperty = textProperty;
    }
    else
    {
        Log::Warning("Property is not actually a text property but was created as one. Name: " + property->GetName(),
            "IntSerializableProperty::IntSerializableProperty("
            "std::shared_ptr<SuperGameEngine::SerializableParser>,"
            "std::shared_ptr<SuperGameEngine::SerializableProperty>)");
        m_serializableProperty = std::make_shared<SuperGameEngine::IntSerializableProperty>();
        m_serializableProperty->SetName(property->GetName());
        m_property = m_serializableProperty;
    }

    m_value = m_serializableProperty->GetDefault();
}

std::shared_ptr<FEventSubscriptions> IntSerializableProperty::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
}

std::shared_ptr<SuperGameEngine::SerializableProperty> IntSerializableProperty::GetEngineProperty() const
{
    return m_property;
}

void IntSerializableProperty::Draw()
{
    if (!m_property)
    {
        return;
    }

    if (*m_dirty)
    {
        ImGui::Text("*");
        ImGui::SameLine();
    }

    ImGui::Text(m_property->GetName().c_str());
    ImGui::SameLine();

    {

        std::string valueAsString = std::to_string(m_value);
        if (TextInput(m_property->GetName() + "_value", valueAsString))
        {
            int attemptedParse = -1;
            if (IntHelpers::TryParse(valueAsString, attemptedParse))
            {
                m_value = attemptedParse;
                UpdateDirtyFlag(true);
            }
        }
    }
}

void IntSerializableProperty::Load(
    const std::shared_ptr<StoredDocumentNode>& node)
{
    m_value = m_serializableProperty->Load(m_serializableParser, node);
    UpdateDirtyFlag(false);
}

std::shared_ptr<ModifiableNode> IntSerializableProperty::Save() const
{
    UpdateDirtyFlag(false);
    return m_serializableProperty->Save(m_serializableParser, m_value);
}

std::shared_ptr<SuperGameEngine::IntSerializableProperty> IntSerializableProperty::GetActualEngineProperty() const
{
    return m_serializableProperty;
}

bool IntSerializableProperty::TextInput(
    const std::string& label, 
    std::string& value) const
{
    const std::string before = value;
    char* charValue = new char[m_defaultTextCapacity];
    size_t written = std::snprintf(charValue, m_defaultTextCapacity, "%s", value.c_str());

    ImGui::PushItemWidth(70);

    const std::string textLabel = "##labelName_" + label;
    ImGui::InputText(textLabel.c_str(), charValue, m_defaultTextCapacity, ImGuiInputTextFlags_CharsDecimal);
    const std::string& after = charValue;

    ImGui::PopItemWidth();

    delete[] charValue;

    value = after;
    return before != after;
}

void IntSerializableProperty::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirty)
    {
        *m_dirty = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}
