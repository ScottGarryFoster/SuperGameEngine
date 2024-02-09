#pragma once

#include "../Events/FEventArguments.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Information about the Location changing on a FPoint
    /// </summary>
    class FPointLocationEventArguments : public FEventArguments
    {
    public:
        /// <summary>
        /// X cordinate.
        /// </summary>
        int X = 0;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        int Y = 0;
    };
}