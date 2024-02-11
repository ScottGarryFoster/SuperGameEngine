#include "SceneLoadPackage.h"
using namespace SuperGameEngine;

SceneLoadPackage::SceneLoadPackage(ContentManager* contentManager, const DirectInput* directInput)
{
    m_contentManager = contentManager;
    m_directInput = directInput;
}

ContentManager* SceneLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

const DirectInput* SuperGameEngine::SceneLoadPackage::GetDirectInput() const
{
    return m_directInput;
}
