#pragma once

#include "../Events/FEventArguments.h"

namespace StandardCLibrary
{
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
    };
}