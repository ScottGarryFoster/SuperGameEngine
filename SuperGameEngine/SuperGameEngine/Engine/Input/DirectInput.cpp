#include "DirectInput.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
DirectInput::DirectInput()
{
    m_directKeyInput = new DirectKeyInput();
}

DirectInput::~DirectInput()
{
    delete m_directKeyInput;
}

void DirectInput::EventUpdate(SDL_Event& e)
{
    m_directKeyInput->EventUpdate(e);
}

const DirectKeyInput* SuperGameEngine::DirectInput::GetDirectKeyInput() const
{
    return m_directKeyInput;
}
