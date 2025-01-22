#pragma once
#include <vector>

#include "FileDialog.h"

namespace SuperGameTools
{
    /// <summary>
    /// An implementation of file dialogs using Tiny File Dialogs.
    /// </summary>
    class TinyFileDialogs : public FileDialog
    {
    public:

        /// <summary>
        /// Open a file dialog and return the result.
        /// </summary>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string OpenFile() const override;

        /// <summary>
        /// Save a file dialog and return the result.
        /// </summary>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string SaveFile() const override;

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
            const override;
    };
}

