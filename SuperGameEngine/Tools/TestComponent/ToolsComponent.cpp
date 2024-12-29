#include "ToolsComponent.h"

#include "../../Engine/Engine/Content/ContentManager.h"
#include "../../Engine/Structural/Packages/ComponentLoadPackage.h"

using namespace SuperGameEngine;

ToolsComponent::ToolsComponent()
{
}

ToolsComponent::~ToolsComponent() = default;

void ToolsComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);

    m_superTexture = componentLoadPackage->
        GetContentManager()->
        Texture()->
        GetTexture(
            R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\collideCircle.png)");

    // Ensure we render.
    SetDoRender(true);
}

void ToolsComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
}

void ToolsComponent::Draw() const
{
    SuperGameComponent::Draw();

    m_superTexture->Draw();
}
