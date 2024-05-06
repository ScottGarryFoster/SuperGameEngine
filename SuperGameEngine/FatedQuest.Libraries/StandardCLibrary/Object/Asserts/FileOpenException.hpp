#pragma once

#include "../FAsserts.h"

namespace StandardCLibrary
{
    /// <summary>
    /// There was an issue openning the given file.
    /// </summary>
    class FileOpenException : public FAsserts
    {
    public:
        /// <summary>
        /// Gets a unique key for this assert.
        /// Ensure nothing else uses it so we may filter exceptions.
        /// </summary>
        /// <returns>A unique text key. </returns>
        FString GetKey() final
        {
            return FString("FileOpenException");
        };

        /// <summary>
        /// The name of the assert as displayed to the user.
        /// </summary>
        /// <returns>A display name. </returns>
        FString GetDisplayKey() final
        {
            return FString("FileOpenException");
        };
    };
}