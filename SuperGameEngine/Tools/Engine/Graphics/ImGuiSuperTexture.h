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
    class ImGuiSuperTexture : public PureSuperTextureWrapper
    {
    public:
        virtual ~ImGuiSuperTexture() override = default;
    };
}


