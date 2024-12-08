#include "SuperGameComponent.h"
#include "../../Engine/Basic/GameTime.h"

using namespace SuperGameEngine;

SuperGameComponent::SuperGameComponent()
{
    m_doRender = false;
    m_isSetup = false;
}

SuperGameComponent::~SuperGameComponent() = default;

void SuperGameComponent::Setup(
    std::shared_ptr<SceneLoadPackage> sceneLoadPackage,
    std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent)
{
    m_sceneLoadPackage = sceneLoadPackage;
    m_parent = parent;
    m_isSetup = true;
}

bool SuperGameComponent::IsSetup() const
{
    return m_isSetup;
}

void SuperGameComponent::Update(const std::shared_ptr<GameTime> gameTime)
{
}

void SuperGameComponent::FixedUpdate(const std::shared_ptr<GameTime> gameTime)
{
}

void SuperGameComponent::Draw() const
{
}

std::shared_ptr<ExtremelyWeakWrapper<GameObject>> SuperGameComponent::GetParent() const
{
    return m_parent;
}

bool SuperGameComponent::DoRender() const
{
    return m_doRender;
}

void SuperGameComponent::SetDoRender(bool newValue)
{
    m_doRender = newValue;
}

std::shared_ptr<SceneLoadPackage> SuperGameComponent::GetSceneLoadPackage() const
{
    return m_sceneLoadPackage;
}
