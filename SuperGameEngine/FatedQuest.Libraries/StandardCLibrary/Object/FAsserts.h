#pragma once

#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Thrown inside a logger when a critcal error occurs.
    /// </summary>
    class FAsserts
    {
    public:
        /// <summary>
        /// Gets a unique key for this assert.
        /// Ensure nothing else uses it so we may filter exceptions.
        /// </summary>
        /// <returns>A unique text key. </returns>
        virtual FString GetKey();

        /// <summary>
        /// The name of the assert as displayed to the user.
        /// </summary>
        /// <returns>A display name. </returns>
        virtual FString GetDisplayKey();
    };
}