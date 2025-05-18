#include "SpriteComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../Packages/ComponentLoadPackage.h"
#include "../../../Engine/Engine/Graphics/Texture/SuperTexture.h"

using namespace SuperGameEngine;

SpriteComponent::SpriteComponent()
{
    m_location = FPoint();
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);
    if (!IsSetup()) return;

    m_superTexture = componentLoadPackage->
        GetContentManager()->
        Texture()->
        GetTexture(
            R"(Engine\TestImages\A_pressed.png)");
    if (!m_superTexture)
    {
        Log::Error("Could not create texture: Engine\TestImages\A_pressed.png", "SpriteComponent::Setup()");
        return;
    }

    // Ensure we render.
    SetDoRender(true);
}

std::string SpriteComponent::TypeName() const
{
    return "SpriteComponent";
}

void SpriteComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
    if (!IsSetup()) return;
}

void SpriteComponent::Draw() const
{
    SuperGameComponent::Draw();
    if (!IsSetup()) return;

    m_superTexture->Draw(m_location);
}

void SpriteComponent::Move(int x, int y)
{
    m_location.SetXYValue(x, y);
}
