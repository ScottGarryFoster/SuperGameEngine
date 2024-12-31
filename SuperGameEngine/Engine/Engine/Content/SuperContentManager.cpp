#include "SuperContentManager.h"

using namespace SuperGameEngine;

SuperContentManager::SuperContentManager()
{
    m_sceneStorageCache = {};
    m_superTextureManager = {};
    m_gamePackage = {};
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

const std::shared_ptr<FatedQuestLibraries::GamePackage> SuperContentManager::GamePackage()
{
    return m_gamePackage;
}

void SuperContentManager::GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

const std::shared_ptr<SceneStorageCache> SuperContentManager::Scene()
{
    return m_sceneStorageCache;
}

void SuperContentManager::GiveSceneCache(const std::shared_ptr<SceneStorageCache>& sceneStorageCache)
{
    m_sceneStorageCache = sceneStorageCache;
}
