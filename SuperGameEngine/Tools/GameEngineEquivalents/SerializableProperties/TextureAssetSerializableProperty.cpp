#include "TextureAssetSerializableProperty.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Structural/Serializable/SerializableProperty.h"
#include "../../../Engine/Structural/Serializable/SerializableParser.h"
#include "../../../Engine/Structural/Serializable/PropertyByType/TextureAssetSerializableProperty.h"

#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

TextureAssetSerializableProperty::TextureAssetSerializableProperty(
    const std::shared_ptr<SuperGameEngine::SerializableParser>& parser,
    const std::shared_ptr<SuperGameEngine::SerializableProperty>& property)
{
    m_onDirtyFlagChanged = std::make_shared<FEvent>();
    m_dirty = std::make_shared<bool>();
    *m_dirty = false;

    m_property = property;
    m_value[0] = '\0';
    m_serializableParser = parser;
    if (std::shared_ptr<SuperGameEngine::TextureAssetSerializableProperty> textProperty =
        std::dynamic_pointer_cast<SuperGameEngine::TextureAssetSerializableProperty>(m_property))
    {
        m_serializableProperty = textProperty;
    }
    else
    {
        Log::Warning("Property is not actually a text property but was created as one. Name: " + property->GetName(),
            "TextureAssetSerializableProperty::TextureAssetSerializableProperty("
            "std::shared_ptr<SuperGameEngine::SerializableParser>,"
            "std::shared_ptr<SuperGameEngine::SerializableProperty>)");
        m_serializableProperty = std::make_shared<SuperGameEngine::TextureAssetSerializableProperty>();
        m_serializableProperty->SetName(property->GetName());
        m_property = m_serializableProperty;
    }

    if (!SetValueFromString(m_serializableProperty->GetDefault()))
    {
        Log::Error("Could not set default data on construct.",
            "TextureAssetSerializableProperty::TextureAssetSerializableProperty("
            "std::shared_ptr<SuperGameEngine::SerializableParser>,"
            "std::shared_ptr<SuperGameEngine::SerializableProperty>)");
    }
}

std::shared_ptr<FEventSubscriptions> TextureAssetSerializableProperty::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
}

std::shared_ptr<SuperGameEngine::SerializableProperty> TextureAssetSerializableProperty::GetEngineProperty() const
{
    return m_property;
}

void TextureAssetSerializableProperty::Draw()
{
    if (!m_property)
    {
        return;
    }

    ImVec2 before = ImGui::GetCursorScreenPos();

    if (*m_dirty)
    {
        ImGui::Text("*");
        ImGui::SameLine();
    }

    ImGui::Text(m_property->GetName().c_str());
    ImGui::SameLine();

    if (*m_dirty)
    {
        ImGui::InputText("##name", m_value, IM_ARRAYSIZE(m_value));
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

    ImVec2 after = ImGui::GetCursorScreenPos();
    EnableDropTarget(before.x, before.y, after.x, after.y);
}

void TextureAssetSerializableProperty::Load(const std::shared_ptr<StoredDocumentNode>& node)
{
    std::string value = m_serializableProperty->Load(m_serializableParser, node);
    if (!SetValueFromString(value))
    {
        Log::Error("Could not set data on load.",
            "TextureAssetSerializableProperty::Load(std::shared_ptr<StoredDocumentNode>)");
    }

    UpdateDirtyFlag(false);
}

std::shared_ptr<ModifiableNode> TextureAssetSerializableProperty::Save() const
{
    std::string str(m_value);
    UpdateDirtyFlag(false);
    return m_serializableProperty->Save(m_serializableParser, str);
}

std::shared_ptr<SuperGameEngine::TextureAssetSerializableProperty> TextureAssetSerializableProperty::GetActualEngineProperty() const
{
    return m_serializableProperty;
}

bool TextureAssetSerializableProperty::SetValueFromString(const std::string& newValue)
{
    size_t written = std::snprintf(m_value, sizeof(m_value), "%s", newValue.c_str());

    if (written >= sizeof(m_value))
    {
        Log::Error("Text storage too small. Needed: " + std::to_string(written + 1),
            "TextureAssetSerializableProperty::SetValueFromString(std::string)");
        return false;
    }

    if (written < 0 || written > sizeof(m_value))
    {
        Log::Error("Encoding error occurred.",
            "TextureAssetSerializableProperty::SetValueFromString(std::string)");
        return false;
    }

    return true;
}

void TextureAssetSerializableProperty::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirty)
    {
        *m_dirty = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}

void TextureAssetSerializableProperty::EnableDropTarget(float xTop, float yTop, float xBottom, float yBottom)
{
    // Try to make a box which encapsulates the element.
    // We use the 'before' 'after' and window (before width can be weird)
    // To align a drag area.
    auto before = ImVec2(xTop, yTop);
    auto after = ImVec2(xBottom, yBottom);
    ImVec2 windowSize = ImGui::GetWindowSize();
    auto size = ImVec2(windowSize.x - 16, after.y - before.y - 7);
    auto position = ImVec2(before.x, before.y + 2);
    ImGui::SetCursorScreenPos(position);

    // Create drag behaviour over the area. Set this to button if you think the area is wrong (to see the area)
    ImGui::InvisibleButton("##drag_area", size);
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetPackagePath"))
        {
            std::string originalValue = m_value;
            const char* droppedData = static_cast<const char*>(payload->Data);
            if (strlen(droppedData) > m_stringLimit)
            {
                Log::Error("Dragged and drop variable name too long. "
                           "Cannot be longer than: " + std::to_string(m_stringLimit),
                    "TextureAssetSerializableProperty");
            }

            snprintf(m_value, sizeof(m_value), "%s", droppedData);

            if (!StringHelpers::Equals(originalValue,m_value, CaseSensitivity::IgnoreCase))
            {
                UpdateDirtyFlag(true);
            }
        }
        ImGui::EndDragDropTarget();
    }
}