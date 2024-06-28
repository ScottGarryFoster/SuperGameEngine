#include "SceneLoadPackage.h"
using namespace SuperGameEngine;

SceneLoadPackage::SceneLoadPackage(
    ContentManager* contentManager, 
    const DirectInput* directInput,
    TechniqueRenderer* techniqueRenderer,
    FrameTiming* frameTimings,
    CollisionQuery* collisionQuery,
    std::shared_ptr<PackageContents> packageContents)
{
    m_contentManager = contentManager;
    m_directInput = directInput;
    m_techniqueRenderer = techniqueRenderer;
    m_frameTiming = frameTimings;
    m_collisionQuery = collisionQuery;
    m_packageContents = packageContents;
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

CollisionQuery* SceneLoadPackage::GetCollisionQuery() const
{
    return m_collisionQuery;
}

PackageContents* SceneLoadPackage::GetPackageContents() const
{
    return m_packageContents.get();
}
