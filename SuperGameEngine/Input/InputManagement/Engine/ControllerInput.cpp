#include "ControllerInput.h"

using namespace SuperGameInput;

ControllerInput::ControllerInput()
{
}

void ControllerInput::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

void ControllerInput::Update()
{
}
