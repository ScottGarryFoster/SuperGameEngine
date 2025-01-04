#pragma once
#include <memory>
#include "FileDialog.h"

namespace SuperGameTools
{
    /// <summary>
    /// Provides file dialogs for the platform you are on.
    /// </summary>
    class FileDialogProvider
    {
    public:
        FileDialogProvider();

        /// <summary>
        /// Get a new file dialog for your given platform.
        /// </summary>
        /// <returns>A method to open file dialogs. </returns>
        std::shared_ptr<FileDialog> GetFileDialog() const;

    private:
        /// <summary>
        /// Cached version of the file dialog provided.
        /// </summary>
        std::shared_ptr<FileDialog> m_fileDialog;
    };
}
