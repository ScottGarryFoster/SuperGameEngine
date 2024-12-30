#include "SuperGrandScenePackage.h"
#include <utility>

#include "SuperSceneLoadPackage.h"

using namespace SuperGameEngine;

SuperGrandScenePackage::SuperGrandScenePackage()
{
    m_createdSceneLoadPackage = false;
    m_contentManager = {};
    m_sceneLoadPackage = {};
}

std::shared_ptr<ContentManager> SuperGrandScenePackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperGrandScenePackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = std::move(contentManager);
    AttemptToCreateASceneLoadPackage();
}

std::shared_ptr<SceneLoadPackage> SuperGrandScenePackage::GetSceneLoadPackage() const
{
    return m_sceneLoadPackage;
}

void SuperGrandScenePackage::AttemptToCreateASceneLoadPackage()
{
    if (!m_createdSceneLoadPackage)
    {
        auto sceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();
        sceneLoadPackage->SetContentManager(m_contentManager);
        m_sceneLoadPackage = sceneLoadPackage;

        m_createdSceneLoadPackage = true;
    }
}
