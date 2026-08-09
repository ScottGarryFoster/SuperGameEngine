#include "ViewportToolsSettings.h"
#include "../../../../FatedQuest.Libraries/StandardObjects/AllReferences.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ViewportToolsSettings::ViewportToolsSettings(const std::shared_ptr<ModifiableUniversalObjectData>& data)
{
    for (const ViewportToolsSettingsShortcutName& shortcutName : EViewportToolsSettingsShortcutName::ToVector())
    {
        m_shortcuts.insert_or_assign(shortcutName, SuperGameInput::KeyCode::Unknown);
    }

    m_universalObjectData = data;
}

void ViewportToolsSettings::SettingsHaveUpdated()
{
    for (const ViewportToolsSettingsShortcutName& shortcutName : EViewportToolsSettingsShortcutName::ToVector())
    {
        const std::string& shortcutSavedName = EViewportToolsSettingsShortcutName::ToString(shortcutName);
        if (m_universalObjectData->IsStringLoaded(shortcutSavedName))
        {
            SuperGameInput::KeyCode code = SuperGameInput::EKeyCode::FromString(m_universalObjectData->GetString(EViewportToolsSettingsShortcutName::ToString(shortcutName)));
            m_shortcuts.at(shortcutName) = code;
        }
    }
}

SuperGameInput::KeyCode ViewportToolsSettings::GetKeyShortcut(ViewportToolsSettingsShortcutName shortcutName) const
{
    return m_shortcuts.at(shortcutName);
}
