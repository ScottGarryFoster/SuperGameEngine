#pragma once

#include "../FException.h"

namespace StandardCLibrary
{
    /// <summary>
    /// A reference is null and it should not be.
    /// </summary>
    class SystemNullReference : public FException
    {
    public:
        /// <summary>
        /// Gets a unique key for this exception.
        /// Ensure nothing else uses it so we may filter exceptions.
        /// </summary>
        /// <returns>A unique text key. </returns>
        FString GetKey() final
        {
            return FString("SystemNullReference");
        };

        /// <summary>
        /// The name of the exception as displayed to the user.
        /// </summary>
        /// <returns>A display name. </returns>
        FString GetDisplayKey() final
        {
            return FString("SystemNullReference");
        };
    };
}