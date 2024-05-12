#pragma once

#include "../Events/FEventArguments.h"

namespace StandardCLibrary
{
    class FVector2D;

    /// <summary>
    /// Information about the Location changing on a FVector
    /// </summary>
    class FVectorLocationEventArguments : public FEventArguments
    {
    public:
        /// <summary>
        /// X cordinate.
        /// </summary>
        float X = 0;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        float Y = 0;

        /// <summary>
        /// The object which called the event.
        /// </summary>
        const FVector2D* Caller = nullptr;
    };
}