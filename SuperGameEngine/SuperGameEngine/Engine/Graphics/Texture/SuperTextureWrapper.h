#pragma once
#include <memory>
#include "Texture.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture 
    /// </summary>
    class SuperTextureWrapper
    {
    public:
        SuperTextureWrapper(std::shared_ptr<Texture> texture);

    private:
        /// <summary>
        /// Reference to the texture to render.
        /// </summary>
        std::shared_ptr<Texture> m_texture;
    };
}