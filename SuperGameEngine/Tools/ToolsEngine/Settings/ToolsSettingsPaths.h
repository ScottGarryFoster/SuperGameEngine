#pragma once
#include <memory>

#include "SettingsPaths.h"
#include <string>

namespace FatedQuestLibraries
{
    class FilePaths;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Helps when finding paths.
    /// </summary>
    class ToolsSettingsPaths : public SettingsPaths
    {
    public:
        /// <summary>
        /// Returns the directory settings should be saved in for tools.
        /// </summary>
        /// <returns>Returns the directory settings should be saved in for tools. </returns>
        virtual std::string SettingDirectory() const override;
    };
}
