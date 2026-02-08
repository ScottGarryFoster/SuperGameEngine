#include "SuperTextureFactory.h"
#include "Engine/Graphics/Texture/Texture.h"

using namespace SuperGameEngine;

std::shared_ptr<PureTexture> SuperTextureFactory::Create(const std::shared_ptr<SDLRendererReader>& renderer) const
{
    return std::make_shared<Texture>(renderer);
}
