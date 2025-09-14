#include "ToolsGameComponent.h"

#include "../../Engine/Engine/Content/ContentManager.h"
#include "../../Engine/Engine/Graphics/Texture/SuperTexture.h"
#include "../../Engine/Structural/Packages/ComponentLoadPackage.h"

using namespace SuperGameEngine;

ToolsGameComponent::ToolsGameComponent()
{
}

ToolsGameComponent::~ToolsGameComponent() = default;

void ToolsGameComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::weak_ptr <GameObject>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);
    if (!IsSetup()) return;

    m_superTexture = componentLoadPackage->
        GetContentManager()->
        Texture()->
        GetTexture(
            R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\collideCircle.png)");

    // Ensure we render.
    SetDoRender(true);
}

std::string ToolsGameComponent::TypeName() const
{
    return "ToolsComponent";
}

void ToolsGameComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
    if (!IsSetup()) return;
}

void ToolsGameComponent::Draw() const
{
    SuperGameComponent::Draw();
    if (!IsSetup()) return;

    m_superTexture->Draw();
}
