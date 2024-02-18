#pragma once

#include "../FAsserts.h"

namespace StandardCLibrary
{
    /// <summary>
    /// A reference is null and it should not be.
    /// </summary>
    class SystemNullReference : public FAsserts
    {
    public:
        /// <summary>
        /// Gets a unique key for this assert.
        /// Ensure nothing else uses it so we may filter exceptions.
        /// </summary>
        /// <returns>A unique text key. </returns>
        FString GetKey() final
        {
            return FString("SystemNullReference");
        };

        /// <summary>
        /// The name of the assert as displayed to the user.
        /// </summary>
        /// <returns>A display name. </returns>
        FString GetDisplayKey() final
        {
            return FString("SystemNullReference");
        };
    };
}