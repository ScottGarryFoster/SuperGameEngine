#include "TestComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../Packages/SceneLoadPackage.h"

using namespace SuperGameEngine;

TestComponent::TestComponent()
{
}

TestComponent::~TestComponent() = default;

void TestComponent::Setup(
    std::shared_ptr<SceneLoadPackage> sceneLoadPackage, 
    GameObject* parent)
{
    SuperGameComponent::Setup(sceneLoadPackage, parent);

    m_superTexture = sceneLoadPackage->
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
