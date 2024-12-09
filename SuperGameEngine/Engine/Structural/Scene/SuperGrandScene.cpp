#include "SuperGrandScene.h"

#include "../Packages/GrandScenePackage.h"
#include "../Packages/SuperSceneLoadPackage.h"

using namespace SuperGameEngine;

void SuperGrandScene::Setup(std::shared_ptr<GrandScenePackage> grandScenePackage)
{
    m_grandScenePackage = grandScenePackage;

    // Setup Scene load package
    auto superSceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();
    superSceneLoadPackage->SetContentManager(m_grandScenePackage->GetContentManager());
    m_sceneLoadPackage = superSceneLoadPackage;

    m_isSetup = true;
}

bool SuperGrandScene::IsSetup() const
{
    return m_isSetup;
}

void SuperGrandScene::Update(const std::shared_ptr<GameTime> gameTime)
{
}

void SuperGrandScene::Draw() const
{
}
