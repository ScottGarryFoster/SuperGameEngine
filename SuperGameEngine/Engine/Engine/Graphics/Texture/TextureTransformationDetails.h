#pragma once
#include "TextureOrientation.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Defines the rotation of a given texture.
    /// This is used when giving the rotation to a texture directly.
    /// </summary>
    struct TextureTransformationDetails
    {
    public:
        /// <summary>
        /// The angle to rotate.
        /// </summary>
        double Angle = 0;

        /// <summary>
        /// The center to rotate around.
        /// </summary>
        int CenterX = 0;

        /// <summary>
        /// The center to rotate around.
        /// </summary>
        int CenterY = 0;

        /// <summary>
        /// Defines how to flip a given texture.
        /// </summary>
        TextureOrientation Orientation;
    };
}
