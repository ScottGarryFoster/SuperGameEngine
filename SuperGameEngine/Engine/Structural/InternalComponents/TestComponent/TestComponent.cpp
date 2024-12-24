#include "TestComponent.h"

#include <iostream>

#include "../../../Engine/Basic/GameTime.h"
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

    /*m_sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));

    auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->GetComponent("SpriteComponent"));
    if (sprite)
    {
        std::cout << "On Setup" << std::endl;
    }*/

    //auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));
    //std::weak_ptr sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));


    for (int i = 0; i < 150; ++i)
    {
        auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));

        sprite->Move((int)(i * 2), i);
        //std::cout << sprite->GetX();
        //std::cout << sprite->GetY();
        //std::cout << "\n";

        m_bunchOfComponents.push_back(sprite);
    }
}

void TestComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);

    /*if (gameTime->AllTime() > 10000)
    {
        for (size_t i = 0; i < m_bunchOfComponents.size(); ++i)
        {
            m_bunchOfComponents[i]->Destroy();
            m_bunchOfComponents[i] = std::shared_ptr<SpriteComponent>();
        }

        m_bunchOfComponents.clear();
    }*/

}