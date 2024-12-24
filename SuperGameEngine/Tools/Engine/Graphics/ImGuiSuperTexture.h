#pragma once
#include "../../../Engine/Engine/Graphics/Texture/SuperTexture.h"

namespace SuperGameEngine
{
    class Texture;
}

using namespace SuperGameEngine;

namespace SuperGameTools
{
    /// <summary>
    /// An Imgui Texture
    /// </summary>
    class ImGuiSuperTexture : public SuperTexture
    {
    public:
        virtual ~ImGuiSuperTexture() override = default;
    };
}


