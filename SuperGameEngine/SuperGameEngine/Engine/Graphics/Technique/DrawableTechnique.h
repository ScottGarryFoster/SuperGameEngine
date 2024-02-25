#pragma once
#include <SDL.h>

#include "../../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The basic concept of being drawable to the screen.
    /// </summary>
    class DrawableTechnique : public Object
    {
    public:
        /// <summary>
        /// Draw to the screen.
        /// </summary>
        virtual void Draw(SDL_Renderer* renderer) = 0;
    };
}


