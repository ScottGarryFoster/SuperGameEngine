#include "SuperComponentLoadPackage.h"

#include <utility>

using namespace SuperGameEngine;

std::shared_ptr<ContentManager> SuperComponentLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperComponentLoadPackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = std::move(contentManager);
}
