#include "PlayerControllerComponent.h"
#include "../../GameObject/GameObject.h"
#include "../Spatial/TransformComponent.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

void PlayerControllerComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);
}

bool PlayerControllerComponent::Update(GameTime gameTime)
{
    GameComponent::Update(gameTime);

    float speed = 0.5f;
    TransformComponent* transform = GameComponent::GetParent()->GetTransform();
    FVector2D* location = transform->GetLocation();
    const DirectKeyInput* input = GameComponent::m_loadPackage->GetDirectInput()->GetDirectKeyInput();

    bool haveMovedX = false;
    bool haveMovedY = false;
    float movementX = 0;
    float movementY = 0;
    if (input->KeyDown(InputKeyCode::D))
    {
        movementX = speed * gameTime.TicksSinceLastFrame;
        haveMovedX = true;
    }
    else if (input->KeyDown(InputKeyCode::A))
    {
        movementX = -(speed * gameTime.TicksSinceLastFrame);
        haveMovedX = true;
    }

    if (input->KeyDown(InputKeyCode::W))
    {
        movementY = -(speed * gameTime.TicksSinceLastFrame);
        haveMovedY = true;
    }
    else if (input->KeyDown(InputKeyCode::S))
    {
        movementY = (speed * gameTime.TicksSinceLastFrame);
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

    float newX = location->GetX() + movementX;
    float newY = location->GetY() + movementY;
    if (haveMoved)
    {
        location->SetXYValue(newX, newY);
    }

    return true;
}
