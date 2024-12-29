#include "SuperGameComponent.h"
#include "../../Engine/Basic/GameTime.h"
#include "../../FatedQuestReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperGameComponent::SuperGameComponent()
{
    m_doRender = false;
    m_isSetup = false;
    m_isDestroyed = false;
}

SuperGameComponent::~SuperGameComponent() = default;

SuperGameComponent::SuperGameComponent(const SuperGameComponent& other)
{
    m_doRender = other.m_doRender;
    m_isSetup = other.m_isSetup;
    m_isDestroyed = other.m_isDestroyed;
    m_parent = other.m_parent;
    m_loadPackage = other.m_loadPackage;
}

SuperGameComponent& SuperGameComponent::operator=(const SuperGameComponent& other)
{
    if(this == &other) return *this;

    m_doRender = other.m_doRender;
    m_isSetup = other.m_isSetup;
    m_isDestroyed = other.m_isDestroyed;
    m_parent = other.m_parent;
    m_loadPackage = other.m_loadPackage;

    return *this;
}

SuperGameComponent::SuperGameComponent(SuperGameComponent&& other) noexcept
{
    m_doRender = other.m_doRender;
    m_isSetup = other.m_isSetup;
    m_isDestroyed = other.m_isDestroyed;
    m_parent = other.m_parent;
    m_loadPackage = other.m_loadPackage;

    other.m_parent = {};
    other.m_loadPackage = {};
    other.m_isDestroyed = true;
}

SuperGameComponent& SuperGameComponent::operator=(SuperGameComponent&& other) noexcept
{
    if (this == &other) return *this;

    m_doRender = other.m_doRender;
    m_isSetup = other.m_isSetup;
    m_isDestroyed = other.m_isDestroyed;
    m_parent = other.m_parent;
    m_loadPackage = other.m_loadPackage;

    other.m_parent = {};
    other.m_loadPackage = {};
    other.m_isDestroyed = true;

    return *this;
}

void SuperGameComponent::Setup(
    const std::shared_ptr<ComponentLoadPackage>& sceneLoadPackage,
    const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent)
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

void SuperGameComponent::Load(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    
}

std::shared_ptr<StoredDocumentNode> SuperGameComponent::Save()
{
    Log::Error("Save called on SuperGameComponent.");
    return {};
}

std::shared_ptr<ComponentLoadPackage> SuperGameComponent::GetSceneLoadPackage() const
{
    return m_loadPackage;
}

void SuperGameComponent::AddAnySuperGameComponentSaves(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
    if (!documentNode)
    {
        return;
    }


}
