#pragma once
#include <memory>
#include <string>

#include "../../../Engine/Engine/Content/SuperTextureManager.h"

namespace SuperGameEngine
{
    class SuperTexture;
}

using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ImGuiSuperTextureWrapper;
    class ImGuiTexture;

    class ImGuiTextureManager : public SuperTextureManager
    {
    public:
        explicit ImGuiTextureManager(
            const std::shared_ptr<SDLRendererReader>& renderer,
            const std::shared_ptr<GamePackage>& gamePackage,
            const ContentFactories& contentFactories);
        virtual ~ImGuiTextureManager() override = default;
    };
}
