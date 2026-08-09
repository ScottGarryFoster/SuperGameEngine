#include "ImGuiTextureManager.h"
#include "../Graphics/ImGuiTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ImGuiTextureManager::ImGuiTextureManager(
    const std::shared_ptr<SDLRendererReader>& renderer,
    const std::shared_ptr<GamePackage>& gamePackage, 
    const ContentFactories& contentFactories)
    : SuperTextureManager(renderer, gamePackage, contentFactories)
{
}