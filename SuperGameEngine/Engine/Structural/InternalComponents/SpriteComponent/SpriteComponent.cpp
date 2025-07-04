#include "SpriteComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../Packages/ComponentLoadPackage.h"
#include "../../../Engine/Structural/Assets/Texture/SuperTextureAsset.h"

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

    m_textureAsset = componentLoadPackage->GetContentManager()->Texture()->GetTextureAsset(R"(Engine\TestImages\Small-8-Direction-Characters_by_AxulArt.png)");
    if (!m_textureAsset)
    {
        Log::Error("Could not create texture: Engine\\TestImages\\Small-8-Direction-Characters_by_AxulArt.png", "SpriteComponent::Setup()");
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

    if (!m_textureAsset)
    {
        return;
    }

    m_textureAsset->Draw(1);
}

void SpriteComponent::Move(int x, int y)
{
    m_location.SetXYValue(x, y);
}
