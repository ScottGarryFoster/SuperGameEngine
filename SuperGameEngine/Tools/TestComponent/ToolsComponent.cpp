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
    if (!IsSetup()) return;

    m_superTexture = componentLoadPackage->
        GetContentManager()->
        Texture()->
        GetTexture(
            R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\collideCircle.png)");

    // Ensure we render.
    SetDoRender(true);
}

std::string ToolsComponent::TypeName() const
{
    return "ToolsComponent";
}

void ToolsComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
    if (!IsSetup()) return;
}

void ToolsComponent::Draw() const
{
    SuperGameComponent::Draw();
    if (!IsSetup()) return;

    m_superTexture->Draw();
}
