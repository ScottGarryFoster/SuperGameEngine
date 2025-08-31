#include "Vector2FSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../../Engine/Structural/Serializable/SerializableParser.h"
#include "../../../Engine/Structural/Serializable/PropertyByType/Vector2FSerializableProperty.h"

#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

Vector2FSerializableProperty::Vector2FSerializableProperty(
    const std::shared_ptr<SuperGameEngine::SerializableParser>& parser,
    const std::shared_ptr<SuperGameEngine::SerializableProperty>& property)
{
    m_onDirtyFlagChanged = std::make_shared<FEvent>();
    m_dirty = std::make_shared<bool>();
    *m_dirty = false;

    m_property = property;

    m_serializableParser = parser;
    if (std::shared_ptr<SuperGameEngine::Vector2FSerializableProperty> textProperty =
        std::dynamic_pointer_cast<SuperGameEngine::Vector2FSerializableProperty>(m_property))
    {
        m_serializableProperty = textProperty;
    }
    else
    {
        Log::Warning("Property is not actually a text property but was created as one. Name: " + property->GetName(),
            "TextSerializableProperty::TextSerializableProperty("
            "std::shared_ptr<SuperGameEngine::SerializableParser>,"
            "std::shared_ptr<SuperGameEngine::SerializableProperty>)");
        m_serializableProperty = std::make_shared<SuperGameEngine::Vector2FSerializableProperty>();
        m_serializableProperty->SetName(property->GetName());
        m_property = m_serializableProperty;
    }

    m_value = m_serializableProperty->GetDefault();
}

std::shared_ptr<FEventSubscriptions> Vector2FSerializableProperty::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
}

std::shared_ptr<SuperGameEngine::SerializableProperty> Vector2FSerializableProperty::GetEngineProperty() const
{
    return m_property;
}

void Vector2FSerializableProperty::Draw()
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
        ImGui::Text("X:");
        ImGui::SameLine();

        std::string valueAsString = FloatingPointHelpers::RemoveUnneededZeros(m_value.GetX());
        if (TextInput(m_property->GetName() + "_X", valueAsString))
        {
            float attemptedParse = -1;
            if (FloatingPointHelpers::TryParse(valueAsString, attemptedParse))
            {
                m_value.SetX(attemptedParse);
                UpdateDirtyFlag(true);
            }
        }
    }

    ImGui::SameLine();

    {
        ImGui::Text("Y:");
        ImGui::SameLine();

        std::string valueAsString = FloatingPointHelpers::RemoveUnneededZeros(m_value.GetY());
        if (TextInput(m_property->GetName() + "_Y", valueAsString))
        {
            float attemptedParse = -1;
            if (FloatingPointHelpers::TryParse(valueAsString, attemptedParse))
            {
                m_value.SetY(attemptedParse);
                UpdateDirtyFlag(true);
            }
        }
    }
}

void Vector2FSerializableProperty::Load(const std::shared_ptr<StoredDocumentNode>& node)
{
    m_value = m_serializableProperty->Load(m_serializableParser, node);
    UpdateDirtyFlag(false);
}

std::shared_ptr<ModifiableNode> Vector2FSerializableProperty::Save() const
{
    UpdateDirtyFlag(false);
    return m_serializableProperty->Save(m_serializableParser, m_value);
}

std::shared_ptr<SuperGameEngine::Vector2FSerializableProperty> Vector2FSerializableProperty::GetTextProperty() const
{
    return m_serializableProperty;
}

void Vector2FSerializableProperty::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirty)
    {
        *m_dirty = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}

bool Vector2FSerializableProperty::TextInput(const std::string& label, std::string& value) const
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
