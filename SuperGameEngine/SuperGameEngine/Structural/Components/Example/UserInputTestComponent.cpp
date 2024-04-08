#include "UserInputTestComponent.h"
#include "../../GameObject/GameObject.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
void UserInputTestComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);
}

bool UserInputTestComponent::Update(GameTime gameTime)
{
    const DirectKeyInput* directInput = GetLoadPackage()->GetDirectInput()->GetDirectKeyInput();
    if (directInput->KeyDown(InputKeyCode::Q))
    {
        Logger::Info(FString("Q key Down"));
    }
    else if (directInput->KeyPressed(InputKeyCode::W))
    {
        Logger::Info(FString("W key Pressed"));
    }
    else if (directInput->KeyUp(InputKeyCode::E))
    {
        Logger::Info(FString("E key Released"));
    }

    return false;
}


