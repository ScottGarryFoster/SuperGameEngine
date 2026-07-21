#pragma once
#include "FColour.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Helps in the construction and manipulation of the <see cref="FColour"/> struct.
    /// </summary>
    class FColourHelpers
    {
    public:
        /// <summary>
        /// Default colours, red.
        /// </summary>
        static constexpr FColour Red { .Red=255, .Green=0, .Blue=0, .Alpha=255};

        /// <summary>
        /// Default colours, green.
        /// </summary>
        static constexpr FColour Green { .Red=0, .Green=255, .Blue=0, .Alpha=255};

        /// <summary>
        /// Default colours, blue.
        /// </summary>
        static constexpr FColour Blue { .Red=0, .Green=0, .Blue=255, .Alpha=255};

        /// <summary>
        /// Default colours, white.
        /// </summary>
        static constexpr FColour White{ .Red=255, .Green=255, .Blue=255, .Alpha=255};

        /// <summary>
        /// Default colours, black.
        /// </summary>
        static constexpr FColour Black{ .Red=0, .Green=0, .Blue=0, .Alpha=255};

        /// <summary>
        /// Default colours, transparent.
        /// </summary>
        static constexpr FColour Transparent{ .Red=0, .Green=0, .Blue=0, .Alpha=0};
    };
}