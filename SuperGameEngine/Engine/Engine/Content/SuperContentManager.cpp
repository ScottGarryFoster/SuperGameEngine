#include "SuperContentManager.h"

using namespace SuperGameEngine;

SuperContentManager::SuperContentManager()
{
}

SuperContentManager::~SuperContentManager()
{
}

const std::shared_ptr<TextureManager> SuperContentManager::Texture()
{
    return m_superTextureManager;
}

void SuperContentManager::GiveSuperTextureManager(
    std::shared_ptr<SuperTextureManager> superTextureManager)
{
    m_superTextureManager = superTextureManager;
}

std::shared_ptr<SuperTextureManager> SuperContentManager::GetSuperTextureManager()
{
    return m_superTextureManager;
}
