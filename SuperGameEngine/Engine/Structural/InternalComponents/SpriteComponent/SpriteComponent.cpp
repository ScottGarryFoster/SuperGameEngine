#include "SpriteComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../Packages/ComponentLoadPackage.h"

using namespace SuperGameEngine;

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Setup(
    std::shared_ptr<ComponentLoadPackage> componentLoadPackage,
    std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);

    m_superTexture = componentLoadPackage->
        GetContentManager()->
        Texture()->
        GetTexture(
            R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\A_pressed.png)");

    // Ensure we render.
    SetDoRender(true);
}

void SpriteComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
}

void SpriteComponent::Draw() const
{
    SuperGameComponent::Draw();

    m_superTexture->Draw(FPoint(200, 200));
}
