#include "SuperSceneLoadPackage.h"
#include "../../Engine/Content/ContentManager.h"

using namespace SuperGameEngine;

std::shared_ptr<ContentManager> SuperSceneLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperSceneLoadPackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = contentManager;
}
