#pragma once
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// Helps when finding paths with settings.
    /// </summary>
    class SettingsPaths
    {
    public:
        /// <summary>
        /// Returns the directory settings should be saved in for tools.
        /// </summary>
        /// <returns>Returns the directory settings should be saved in for tools. </returns>
        virtual std::string SettingDirectory() const = 0;
    };
}
