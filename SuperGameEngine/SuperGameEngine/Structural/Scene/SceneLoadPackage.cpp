#include "SceneLoadPackage.h"
using namespace SuperGameEngine;

SceneLoadPackage::SceneLoadPackage(ContentManager* contentManager)
{
    m_contentManager = contentManager;
}

ContentManager* SceneLoadPackage::GetContentManager() const
{
    return m_contentManager;
}