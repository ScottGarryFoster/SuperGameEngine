#pragma once
#include <string>
#include <vector>

namespace SuperGameTools
{
    /// <summary>
    /// Allows you to open a file dialog.
    /// </summary>
    class FileDialog
    {
    public:
        /// <summary>
        /// Open a file dialog and return the result.
        /// </summary>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string OpenFile() const = 0;

        /// <summary>
        /// Save a file dialog and return the result.
        /// </summary>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string SaveFile() const = 0;

        /// <summary>
        /// Save a file dialog and return the result.
        /// </summary>
        /// <param name="title">Title of the save box. </param>
        /// <param name="defaultFilename">Default filename. </param>
        /// <param name="filters">
        /// Extension with dot for example: ["*.txt"]
        /// </param>
        /// <param name="fileDisplayName">Display name to describe the filters. </param>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string SaveFile(
            const std::string& title,
            const std::string& defaultFilename,
            const std::vector<std::string>& filters,
            const std::string& fileDisplayName)
            const = 0;
    };
}

