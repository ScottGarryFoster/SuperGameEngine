#pragma once
#include <string>

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
    };
}

