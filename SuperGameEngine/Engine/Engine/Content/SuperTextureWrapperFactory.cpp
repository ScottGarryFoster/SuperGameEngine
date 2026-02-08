#include "SuperTextureWrapperFactory.h"
#include "Engine/Graphics/Texture/SuperTextureWrapper.h"

using namespace SuperGameEngine;

std::shared_ptr<PureSuperTextureWrapper> SuperTextureWrapperFactory::Create(const std::shared_ptr<PureTexture>& texture) const
{
    return std::make_shared<SuperTextureWrapper>(texture);
}
