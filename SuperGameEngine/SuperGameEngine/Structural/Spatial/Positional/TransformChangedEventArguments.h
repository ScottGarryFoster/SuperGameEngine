#pragma once
#include "../../../LibraryIncludes.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Information about the Location changing on a FVector
    /// </summary>
    class TransformChangedEventArguments : public FEventArguments
    {
    public:
        /// <summary>
        /// The current location of the transform.
        /// </summary>
        const FVector2D* Location = nullptr;

        /// <summary>
        /// The current Scale.
        /// </summary>
        const FVector2D* Scale = nullptr;

        /// <summary>
        /// The current Rotation.
        /// </summary>
        const FVector2D* Rotation = nullptr;
    };
}