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
        /// Opens a file dialog and returns the result.
        /// </summary>
        /// <param name="title">Title of the window. </param>
        /// <param name="defaultPath">
        /// Default path to open to.
        /// End in a folder separator to open to that folder \\
        /// or enter an actual filename for this to be entered.
        /// </param>
        /// <param name="filters">Filters to use. Enter these as wild card extension: ["*.txt"]. </param>
        /// <param name="fileDisplayName">Description of the filters. </param>
        /// <returns>The file selected. Empty if canceled or nothing selected. </returns>
        virtual std::string OpenFile(
            const std::string& title,
            const std::string& defaultPath,
            const std::vector<std::string>& filters,
            const std::string& fileDisplayName)
            const override;

        /// <summary>
        /// Save a file dialog and return the result.
        /// </summary>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string SaveFile() const override;

        /// <summary>
        /// Save a file dialog and return the result.
        /// </summary>
        /// <param name="title">Title of the save box. </param>
        /// <param name="defaultPath">
        /// Default path to open to.
        /// End in a folder separator to open to that folder \\
        /// or enter an actual filename for this to be entered.
        /// </param>
        /// <param name="filters">
        /// Extension with dot for example: ["*.txt"]
        /// </param>
        /// <param name="fileDisplayName">Display name to describe the filters. </param>
        /// <returns>The result of a file dialog. Empty if cancelled or nothing selected. </returns>
        virtual std::string SaveFile(
            const std::string& title,
            const std::string& defaultPath,
            const std::vector<std::string>& filters,
            const std::string& fileDisplayName)
            const override;
    };
}

