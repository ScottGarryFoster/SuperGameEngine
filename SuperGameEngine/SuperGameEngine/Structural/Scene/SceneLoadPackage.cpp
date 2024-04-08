#include "SceneLoadPackage.h"
using namespace SuperGameEngine;

SceneLoadPackage::SceneLoadPackage(
    ContentManager* contentManager, 
    const DirectInput* directInput,
    TechniqueRenderer* techniqueRenderer,
    FrameTiming* frameTimings)
{
    m_contentManager = contentManager;
    m_directInput = directInput;
    m_techniqueRenderer = techniqueRenderer;
    m_frameTiming = frameTimings;
}

SceneLoadPackage::~SceneLoadPackage()
{
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

FrameTiming* SuperGameEngine::SceneLoadPackage::GetFrameTiming() const
{
    return m_frameTiming;
}
