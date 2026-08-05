#pragma once
#include <map>
#include <memory>

#include "ViewportToolsSettingsShortcutName.h"
#include "../../../Input/InputManagement/Engine/KeyCode.h"

namespace FatedQuestLibraries
{
    class ModifiableUniversalObjectData;
}

namespace SuperGameTools
{
    /// <summary>
    /// The settings for the Viewport Tools
    /// </summary>
    class ViewportToolsSettings
    {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="data">Data these settings pull from.</param>
        ViewportToolsSettings(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& data);

        /// <summary>
        /// Update the data with new settings data.
        /// </summary>
        void SettingsHaveUpdated();

        /// <summary>
        /// Get the value of a defined shortcut.
        /// </summary>
        /// <param name="shortcutName">The name of the shortcut defined by an enum. </param>
        /// <returns>The value of a defined shortcut. </returns>
        SuperGameInput::KeyCode GetKeyShortcut(ViewportToolsSettingsShortcutName shortcutName) const;

    private:

        /// <summary>
        /// The
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData> m_universalObjectData;

        /// <summary>
        /// Shortcuts saved as actual keymaps.
        /// </summary>
        std::map<ViewportToolsSettingsShortcutName, SuperGameInput::KeyCode> m_shortcuts;
    };
}
