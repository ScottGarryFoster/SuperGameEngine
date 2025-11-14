#pragma once
#include <vector>

#include "TextureManager.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Creates, stores and manages all textures in the engine.
    /// </summary>
    class EngineTextureManager : public virtual TextureManager
    {
    public:
        /// <summary>
        /// Remakes all textures the manager holds.
        /// Used after the window has just been destroyed.
        /// Will stop after a single error.
        /// </summary>
        /// <param name="errors">Any errors which occured after remaking textures. </param>
        /// <returns>True means there were not errors. </returns>
        virtual bool RemakeAllTextures(std::vector<std::string>& errors) = 0;
    };
}
