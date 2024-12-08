#include "ToolsComponent.h"

#include "../../Engine/Engine/Content/ContentManager.h"
#include "../../Engine/Structural/Packages/SceneLoadPackage.h"

using namespace SuperGameEngine;

ToolsComponent::ToolsComponent()
{
}

ToolsComponent::~ToolsComponent() = default;

void ToolsComponent::Setup(
    std::shared_ptr<SceneLoadPackage> sceneLoadPackage,
    GameObject* parent)
{
    SuperGameComponent::Setup(sceneLoadPackage, parent);

    m_superTexture = sceneLoadPackage->
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
