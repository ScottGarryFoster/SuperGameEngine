#pragma once

namespace FatedQuestLibraries
{
    /// <summary>
    /// Represents a colour which can be passed to the renderer.
    /// Use FColourHelpers to manipulate this if needed, it is intended to be
    /// kept small and devoid of logic.
    /// </summary>
    struct FColour
    {
    public:

        /// <summary>
        /// The red colour when using RGBA colouring.
        /// </summary>
        uint8_t Red;

        /// <summary>
        /// The green colour when using Green colouring.
        /// </summary>
        uint8_t Green;

        /// <summary>
        /// The blue colour when using RGBA colouring.
        /// </summary>
        uint8_t Blue;

        /// <summary>
        /// The alpha channel when using RGBA colouring.
        /// </summary>
        uint8_t Alpha;
    };
}
