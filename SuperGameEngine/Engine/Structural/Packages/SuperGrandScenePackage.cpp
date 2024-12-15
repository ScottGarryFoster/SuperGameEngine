#include "SuperGrandScenePackage.h"
#include <utility>

using namespace SuperGameEngine;

std::shared_ptr<ContentManager> SuperGrandScenePackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperGrandScenePackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = std::move(contentManager);
}
