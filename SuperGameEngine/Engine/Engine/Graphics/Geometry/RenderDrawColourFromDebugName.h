#pragma once
#include <memory>

#include "DebugColourName.h"

namespace SuperGameEngine
{
    class SDLRendererReader;

    /// <summary>
    /// Switches the render draw colour based on debug colour.
    /// </summary>
    class RenderDrawColourFromDebugName
    {
    public:
        /// <summary>
        /// Set the render draw colour based on DebugColourName.
        /// </summary>
        /// <param name="renderer">Renderer to set on. </param>
        /// <param name="colour">Colour to set to. </param>
        void SetColour(const std::shared_ptr<SDLRendererReader>& renderer, DebugColourName colour) const;
    };
}
