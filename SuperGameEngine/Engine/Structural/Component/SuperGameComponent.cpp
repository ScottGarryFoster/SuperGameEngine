#include "SuperGameComponent.h"
#include "../../Engine/Basic/GameTime.h"
#include "../../FatedQuestReferences.h"
#include "../../Engine/Content/ContentManager.h"
#include "../Packages/ComponentLoadPackage.h"

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
    const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
    const std::weak_ptr <GameObject>& parent)
{
    m_loadPackage = componentLoadPackage;
    m_parent = parent;

    const std::string thisMethod = "SuperGameComponent::Setup(std::shared_ptr<ComponentLoadPackage>,std::shared_ptr<ExtremelyWeakWrapper<GameObject>>)";
    if (!componentLoadPackage)
    {
        Log::Error("Could not find Component Load Package.", thisMethod);
        return;
    }

    if (!componentLoadPackage->GetContentManager())
    {
        Log::Error("Could not find Content Manager.", thisMethod);
        return;
    }

    if (!componentLoadPackage->GetContentManager()->Texture())
    {
        Log::Error("Could not find Texture Manager.", thisMethod);
        return;
    }

    if (!componentLoadPackage->GetContentManager()->GamePackage())
    {
        Log::Error("Could not find Game Package.", thisMethod);
        return;
    }

    m_isSetup = true;
}

std::string SuperGameComponent::TypeName() const
{
    return "SuperGameComponent";
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

std::weak_ptr<GameObject> SuperGameComponent::GetParent() const
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
    //Log::Error("Save called on SuperGameComponent.");
    return {};
}

std::vector<std::shared_ptr<SerializableProperty>> SuperGameComponent::Properties() const
{
    return m_serializableProperties;
}

std::shared_ptr<ComponentLoadPackage> SuperGameComponent::LoadPackage() const
{
    return m_loadPackage;
}

void SuperGameComponent::AddAnySuperGameComponentSaves(const std::shared_ptr<ModifiableNode>& documentNode)
{
    if (!documentNode)
    {
        return;
    }


}
