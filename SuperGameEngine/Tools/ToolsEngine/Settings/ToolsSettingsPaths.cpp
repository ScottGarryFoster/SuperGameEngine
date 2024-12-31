#include "ToolsSettingsPaths.h"
#include "../../FatedQuestLibraries.h"

using namespace SuperGameTools;

std::string ToolsSettingsPaths::SettingDirectory() const
{
    std::string topLevel = Directory::GetTempDirectory();
    if (topLevel.empty())
    {
        topLevel = FilePaths::ApplicationDirectory();
    }

    if (topLevel.empty())
    {
        Log::Error("Could not get temp or application directory, therefore I do not know where settings go.",
            "ToolsSettingsPaths::SettingDirectory()");
        return {};
    }

    std::string settingsFolder = Directory::CombinePath(topLevel, "FatedQuest", "Tools", "Settings");
    if (!Directory::Exists(settingsFolder))
    {
        if (!Directory::CreateDirectories(settingsFolder))
        {
            Log::Error("Directory does not exist and could not create. Something is wrong. Path: " + settingsFolder,
                "ToolsSettingsPaths::SettingDirectory()");
        }
    }

    return settingsFolder;
}
