#pragma once
#include "../../../Engine/Engine/Graphics/Texture/SuperTexture.h"
#include "Engine/Graphics/Texture/SuperTextureWrapper.h"

namespace SuperGameEngine
{
    class Texture;
}

using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ImGuiTexture;

    /// <summary>
    /// An Imgui Texture
    /// </summary>
    /// <remarks>
    /// If you are here and confused look at ImGuiSuperTextureWrapper.
    /// This is included as a way to include just enough for some classes but not others.
    /// </remarks>
    class ImGuiSuperTexture : public PureSuperTextureWrapper
    {
    public:
        virtual ~ImGuiSuperTexture() override = default;
    };
}


