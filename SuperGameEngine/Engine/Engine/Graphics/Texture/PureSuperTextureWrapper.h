#pragma once
#include "SuperTexture.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The pure methods of the Super Texture Wrapper.
    /// </summary>
    class PureSuperTextureWrapper : public SuperTexture
    {
    public:

        /// <summary>
        /// Remakes the texture if possible.
        /// Used when the window has just been torn apart and is now new,
        /// or if the filepath now have new data within it.
        /// Will remake in the same way it was last successfully attempted.
        /// </summary>
        virtual bool Remake(std::vector<std::string>& errors) = 0;
    };
}
