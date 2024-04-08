#include "PlayerControllerComponent.h"
#include "../../GameObject/GameObject.h"
#include "../Spatial/TransformComponent.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

PlayerControllerComponent::PlayerControllerComponent() : GameComponent()
{
    m_useKeyboard = true;
}

PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);

    m_simpleRigidbodyComponent = GetParent()->GetGameComponent<SimpleRigidbodyComponent>();
}

bool PlayerControllerComponent::Update(GameTime gameTime)
{
    GameComponent::Update(gameTime);

    //float speed = (0.1f * gameTime.TicksSinceLastFrame);
    float speed = 100;
    std::shared_ptr<TransformComponent> transform = GameComponent::GetParent()->GetTransform();
    FVector2D* location = transform->GetLocation();

    if (m_useKeyboard)
    {
        MoveByKeyboard(speed, gameTime, location);
    }
    else
    {
        MoveByController(location, speed);
    }

    return true;
}

void PlayerControllerComponent::MoveByKeyboard(float speed, GameTime& gameTime, FVector2D* location)
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
