#include "DirectInput.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

DirectInput::DirectInput(std::shared_ptr<PackageContents> packageContents)
{
    m_packageContents = packageContents;
    m_directKeyInput = new DirectKeyInput();
    m_directXInput = new DirectControllerInput(packageContents);
}

DirectInput::~DirectInput()
{
    delete m_directKeyInput;
    delete m_directXInput;
}

void DirectInput::EventUpdate(SDL_Event& e)
{
    m_directKeyInput->EventUpdate(e);
    m_directXInput->Update();
}

const DirectKeyInput* SuperGameEngine::DirectInput::GetDirectKeyInput() const
{
    return m_directKeyInput;
}

const DirectControllerInput* SuperGameEngine::DirectInput::GetDirectXInput() const
{
    return m_directXInput;
}
