#include "TestComponent.h"

#include <iostream>

#include "../../../../Input/InputManagement/InputHandler.h"
#include "../../../Engine/Basic/GameTime.h"
#include "../../../Engine/Content/ContentManager.h"
#include "../../GameObject/GameObject.h"
#include "../../Packages/ComponentLoadPackage.h"
#include "../../Serializable/SerializableParser.h"
#include "../../Serializable/PropertyByType/TextSerializableProperty.h"
#include "../SpriteComponent/SpriteComponent.h"

using namespace SuperGameEngine;

TestComponent::TestComponent()
{
    m_yPosition = 0;
    m_serial = "default";

    {
        auto property = std::make_shared<TextSerializableProperty>("default");
        property->SetName("Serial");
        m_serializableProperties.emplace_back(property);
    }
}

TestComponent::~TestComponent() = default;

void TestComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent)
{
    SuperGameComponent::Setup(componentLoadPackage, parent);
    if (!IsSetup()) return;

    /*m_sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));

    auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->GetComponent("SpriteComponent"));
    if (sprite)
    {
        std::cout << "On Setup" << std::endl;
    }*/

    //auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));
    //std::weak_ptr sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));

    // Memory Test
    //for (int i = 0; i < 150; ++i)
    //{
    //    auto sprite = std::static_pointer_cast<SpriteComponent>(parent->Get()->AddComponent("SpriteComponent"));

    //    sprite->Move((int)(i * 2), i);
    //    //std::cout << sprite->GetX();
    //    //std::cout << sprite->GetY();
    //    //std::cout << "\n";

    //    m_bunchOfComponents.push_back(sprite);
    //}

    m_pressed = componentLoadPackage->GetContentManager()->Texture()->GetTexture("Engine\\TestImages\\Input\\Press.png");
    if (!m_pressed)
    {
        Log::Error("Could not create texture in test component.");
    }

    m_pressedAlt = componentLoadPackage->GetContentManager()->Texture()->GetTexture("Engine\\TestImages\\Input\\Press_Green.png");
    if (!m_pressedAlt)
    {
        Log::Error("Could not create texture in test component.");
    }

    SetDoRender(true);
}

void TestComponent::Load(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    m_serial = LoadPackage()->GetParser()->ParseFromParent("Serial", "default", documentNode);
}

std::shared_ptr<StoredDocumentNode> TestComponent::Save()
{
    std::shared_ptr<ModifiableNode> node = LoadPackage()->GetParser()->Serialize(std::make_shared<TestComponent>(*this));
    AddAnySuperGameComponentSaves(node);

    std::vector<std::shared_ptr<ModifiableNode>> children;
    children.emplace_back(LoadPackage()->GetParser()->Serialize("Serial", m_serial, "default"));

    node->SetFirstChild(children.at(0));

    return node;
}

std::string TestComponent::TypeName() const
{
    return "TestComponent";
}

void TestComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
    SuperGameComponent::Update(gameTime);
    if (!IsSetup()) return;

    m_serial = "FromUpdate";

    if (!m_pressed)
    {
        return;
    }

    ++m_yPosition;
    if (m_yPosition == 720)
    {
        m_yPosition = 0;
    }

    if (!LoadPackage()->GetInput())
    {
        Log::Error("No input");
        return;
    }
    m_isPressed = LoadPackage()->GetInput()->ButtonDown(UniversalControllerButton::LeftTrigger);

    // Pressed is very quick. So much so you'll likely not see it change in the example.
    if (LoadPackage()->GetInput()->ButtonPressed(UniversalControllerButton::LeftTrigger))
    {
        Log::Info("ButtonPressed");
    }
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


void TestComponent::Draw() const
{
    SuperGameComponent::Draw();
    if (!IsSetup()) return;

    if (!m_pressed)
    {
        return;
    }

    m_pressed->Draw(FPoint(200, m_yPosition));

    if (m_isPressed)
    {
        m_pressed->Draw();
    }
    else
    {
        m_pressedAlt->Draw();
    }
}