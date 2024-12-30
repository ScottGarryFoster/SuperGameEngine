#include "EnginePackageConverter.h"

#include "SuperSceneLoadPackage.h"
#include "GrandScenePackage.h"

using namespace SuperGameEngine;

std::shared_ptr<SceneLoadPackage> EnginePackageConverter::Convert(
    const std::shared_ptr<GrandScenePackage>& grandScenePackage)
{
    auto superSceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();
    superSceneLoadPackage->SetContentManager(grandScenePackage->GetContentManager());

    return superSceneLoadPackage;
}
