#include "PlayerControllerComponent.h"
#include "../../GameObject/GameObject.h"
#include "../Spatial/TransformComponent.h"
#include "../Visual/SpriteComponent.h"
#include "../Visual/TextComponent.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

PlayerControllerComponent::PlayerControllerComponent() : GameComponent()
{
    m_useKeyboard = true;
    m_speed = 100;

    gameObjectt = std::shared_ptr<GameObject>();

    deleteCycle = 0;
}

PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);

    m_simpleRigidbodyComponent = GetParent()->GetGameComponent<SimpleRigidbodyComponent>();
}

bool PlayerControllerComponent::Update(const GameTime gameTime)
{
    GameComponent::Update(gameTime);

    //float speed = (0.1f * gameTime.TicksSinceLastFrame);
    std::shared_ptr<TransformComponent> transform = GameComponent::GetParent()->GetTransformComponent();
    const FVector2D* location = transform->GetLocation();
    FVector2D* locationCopy = new FVector2D(*location);

    if (m_useKeyboard)
    {
        MoveByKeyboard(m_speed, gameTime, locationCopy);

        deleteCycle += gameTime.TicksSinceLastFrame;
        if (deleteCycle > 10)
        {
            deleteCycle = 0;
            // Test for making new Game Objects [#20]
            const DirectKeyInput* input =
                GameComponent::GetLoadPackage()->GetDirectInput()->GetDirectKeyInput();
            if (!gameObjectt)
                //if (!gameObjectt && input->KeyDown(InputKeyCode::N))
            {
                gameObjectt = GetParent()->CreateNewGameObject();
                gameObjectt->GetTransform()->SetLocation(500, 500);
                gameObjectt->AddComponent<SpriteComponent>();
                std::shared_ptr<TextComponent> tc = gameObjectt->AddComponent<TextComponent>();
                tc->SetText(FText("NEW"));
            }
            else if (gameObjectt)
                //else if (gameObjectt && input->KeyDown(InputKeyCode::M))
            {
                gameObjectt->Destroy();
            }
        }

    }
    else
    {
        MoveByController(locationCopy, m_speed);
    }

    delete locationCopy;


    return true;
}

void PlayerControllerComponent::SetSpeed(float newValue)
{
    m_speed = newValue;
}

void PlayerControllerComponent::OnGameObjectDestroyed(const Guid& guid)
{
    if (gameObjectt)
    {
        gameObjectt = std::shared_ptr<GameObject>();
    }
}

void PlayerControllerComponent::MoveByKeyboard(float speed, const GameTime& gameTime, FVector2D* location)
{
    const DirectKeyInput* input = 
        GameComponent::GetLoadPackage()->GetDirectInput()->GetDirectKeyInput();

    bool haveMovedX = false;
    bool haveMovedY = false;
    float movementX = 0;
    float movementY = 0;
    if (input->KeyDown(InputKeyCode::D))
    {
        movementX = speed;
        haveMovedX = true;
    }
    else if (input->KeyDown(InputKeyCode::A))
    {
        movementX = -speed;
        haveMovedX = true;
    }

    if (input->KeyDown(InputKeyCode::W))
    {
        movementY = -speed;
        haveMovedY = true;
    }
    else if (input->KeyDown(InputKeyCode::S))
    {
        movementY = speed;
        haveMovedY = true;
    }

    if (haveMovedX && haveMovedY)
    {
        movementX *= 0.75f;
        movementY *= 0.75f;
    }

    bool haveMoved = false;
    if (haveMovedX || haveMovedY)
    {
        haveMoved = true;
    }

    //float newX = location->GetX() + movementX;
    //float newY = location->GetY() + movementY;
    m_simpleRigidbodyComponent->SetVelocity(movementX, movementY);
    //float newX = location->GetX() + movementX;
    //float newY = location->GetY() + movementY;
    //if (haveMoved)
    //{
    //    location->SetXYValue(newX, newY);
    //}
}

void PlayerControllerComponent::MoveByController(FVector2D* location, float speed)
{
    const DirectControllerInput* controllerInput = GameComponent::GetLoadPackage()->GetDirectInput()->GetDirectXInput();

    int stickX = controllerInput->AxisValue(UniversalControllerAxis::LeftStickX);
    int stickY = controllerInput->AxisValue(UniversalControllerAxis::LeftStickY);
    if (stickX == 0 && stickY == 0)
    {
        m_simpleRigidbodyComponent->SetVelocity(0, 0);
        return;
    }

    FVector2D stick = FVector2D((float)stickX, (float)stickY);

    //FVector2D difference = stick - *location;
    FVector2D direction = stick.Normalize();
    FVector2D velocity = direction * speed;
    FVector2D newPosition = velocity;
    //FVector2D newPosition = *location + velocity;

    //location->SetXYValue(newPosition.GetX(), newPosition.GetY());

    

    m_simpleRigidbodyComponent->SetVelocity(newPosition.GetX(), newPosition.GetY());
}
