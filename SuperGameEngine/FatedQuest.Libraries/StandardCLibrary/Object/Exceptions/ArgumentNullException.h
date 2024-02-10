#pragma once

#include "../FException.h"

namespace StandardCLibrary
{
    /// <summary>
    /// The given arguments are null or nullptr.
    /// </summary>
    class ArgumentNullException : public FException
    {
    public:
        /// <summary>
        /// Gets a unique key for this exception.
        /// Ensure nothing else uses it so we may filter exceptions.
        /// </summary>
        /// <returns>A unique text key. </returns>
        FString GetKey() final
        {
            return FString("ArgumentNullException");
        };

        /// <summary>
        /// The name of the exception as displayed to the user.
        /// </summary>
        /// <returns>A display name. </returns>
        FString GetDisplayKey() final
        {
            return FString("ArgumentNullException");
        };
    };
}