#pragma once

#include "../FAsserts.h"

namespace StandardCLibrary
{
    /// <summary>
    /// The given arguments are null or nullptr.
    /// </summary>
    class ArgumentNullException : public FAsserts
    {
    public:
        /// <summary>
        /// Gets a unique key for this assert.
        /// Ensure nothing else uses it so we may filter exceptions.
        /// </summary>
        /// <returns>A unique text key. </returns>
        FString GetKey() final
        {
            return FString("ArgumentNullException");
        };

        /// <summary>
        /// The name of the assert as displayed to the user.
        /// </summary>
        /// <returns>A display name. </returns>
        FString GetDisplayKey() final
        {
            return FString("ArgumentNullException");
        };
    };
}