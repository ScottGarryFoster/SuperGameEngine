#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// All the information which differs between one Font render operation
    /// and another, passed into a Draw.
    /// </summary>
    struct FontFaceRenderPacketParameters
    {
    public:
        /// <summary>
        /// The text to render on screen.
        /// </summary>
        FText TextToRender = FText();
    };
}