#include "SuperGameObjectLoadPackage.h"

#include <utility>

using namespace SuperGameEngine;

std::shared_ptr<ContentManager> SuperGameObjectLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperGameObjectLoadPackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = std::move(contentManager);
}
