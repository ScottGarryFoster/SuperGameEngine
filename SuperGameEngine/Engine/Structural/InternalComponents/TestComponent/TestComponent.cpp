#include "TestComponent.h"

#include "../../../Engine/Content/ContentManager.h"
#include "../../GameObject/GameObject.h"
#include "../../Packages/ComponentLoadPackage.h"
#include "../SpriteComponent/SpriteComponent.h"

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

    auto sprite2 = std::static_pointer_cast<SpriteComponent>(parent->Get()->GetComponent("SpriteComponent"));
    if (sprite2)
    {
        std::cout << "Before if" << std::endl;
    }
    else
    {
        std::cout << "Before if!" << std::endl;
    }

    m_sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));

    auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->GetComponent("SpriteComponent"));
    if (sprite)
    {
        std::cout << "On Setup" << std::endl;
    }
}

void TestComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
}