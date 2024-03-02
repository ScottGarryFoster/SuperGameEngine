#include "SceneLoadPackage.h"
using namespace SuperGameEngine;

SceneLoadPackage::SceneLoadPackage(
    ContentManager* contentManager, 
    const DirectInput* directInput,
    TechniqueRenderer* techniqueRenderer)
{
    m_contentManager = contentManager;
    m_directInput = directInput;
    m_techniqueRenderer = techniqueRenderer;
}

ContentManager* SceneLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

const DirectInput* SuperGameEngine::SceneLoadPackage::GetDirectInput() const
{
    return m_directInput;
}

TechniqueRenderer* SuperGameEngine::SceneLoadPackage::GetTechniqueRender()
{
    return m_techniqueRenderer;
}
