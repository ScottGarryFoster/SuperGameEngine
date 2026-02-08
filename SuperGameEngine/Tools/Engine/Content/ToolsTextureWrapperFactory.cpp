#include "ToolsTextureWrapperFactory.h"

#include "Engine/Graphics/ImGuiSuperTextureWrapper.h"
#include "Engine/Graphics/ImGuiTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

std::shared_ptr<PureSuperTextureWrapper> ToolsTextureWrapperFactory::Create(const std::shared_ptr<PureTexture>& texture) const
{
    if (auto imGuiTexture = std::dynamic_pointer_cast<ImGuiTexture>(texture))
    {
        return std::make_shared<ImGuiSuperTextureWrapper>(imGuiTexture);
        
    }

    return {};
}
