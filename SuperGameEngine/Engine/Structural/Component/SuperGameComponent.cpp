#include "SuperGameComponent.h"
#include "../../Engine/Basic/GameTime.h"

using namespace SuperGameEngine;

SuperGameComponent::SuperGameComponent()
{
    m_doRender = false;
    m_isSetup = false;
    m_isDestroyed = false;
}

SuperGameComponent::~SuperGameComponent() = default;

void SuperGameComponent::Setup(
    std::shared_ptr<ComponentLoadPackage> sceneLoadPackage,
    std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent)
{
    m_loadPackage = sceneLoadPackage;
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

void SuperGameComponent::Destroy()
{
    m_isDestroyed = true;
}

bool SuperGameComponent::IsDestroyed() const
{
    return m_isDestroyed;
}

void SuperGameComponent::DestroyImmediately()
{
    Destroy();
}

void SuperGameComponent::OnDestroyed()
{
    // Nothing.
}

std::shared_ptr<ComponentLoadPackage> SuperGameComponent::GetSceneLoadPackage() const
{
    return m_loadPackage;
}
