#include "ToolsTextureFactory.h"

#include "Engine/Graphics/ImGuiTexture.h"

using namespace SuperGameEngine;

std::shared_ptr<PureTexture> SuperGameTools::ToolsTextureFactory::Create(const std::shared_ptr<SDLRendererReader>& renderer) const
{
    return std::make_shared<ImGuiTexture>(renderer);
}
