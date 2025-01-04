#pragma once
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
    };
}

