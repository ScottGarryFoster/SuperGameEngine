#include "TestComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../Packages/ComponentLoadPackage.h"

using namespace SuperGameEngine;

TestComponent::TestComponent()
{
}

TestComponent::~TestComponent() = default;

void TestComponent::Setup(
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

void TestComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
}

void TestComponent::Draw() const
{
    SuperGameComponent::Draw();

    m_superTexture->Draw();
}
