#include "SuperGameObject.h"

#include "ComponentFactory.h"

using namespace SuperGameEngine;

SuperGameObject::SuperGameObject()
{
    m_guid = GUIDHelpers::CreateGUID();

    m_sceneGuid = std::shared_ptr<Guid>();
    m_isDestroyed = false;
}

SuperGameObject::~SuperGameObject()
{
    m_guid.reset();
}

std::shared_ptr<Guid> SuperGameObject::GetGuid() const
{
    return m_guid;
}

std::shared_ptr<Guid> SuperGameObject::GetSceneGuid() const
{
    return m_sceneGuid;
}

void SuperGameObject::SetScene(std::shared_ptr<Guid> guid)
{
    m_sceneGuid = guid;
}

void SuperGameObject::Setup(std::shared_ptr<SceneLoadPackage> loadPackage)
{
    m_loadPackage = loadPackage;

    // TODO: Add transform here: EnsureTransformIsOnGameObject();
}

void SuperGameObject::Update(const std::shared_ptr<GameTime> gameTime)
{
}

void SuperGameObject::FixedUpdate(const std::shared_ptr<GameTime> gameTime)
{
}

void SuperGameObject::Draw() const
{
}

std::shared_ptr<GameComponent> SuperGameObject::AddComponent(const std::string& type)
{
    auto component = ComponentFactory::CreateComponent(type);
    if (component)
    {
        return component;
        // TODO: AddActualComponentFromObject(component);
    }

    return component;
}

std::shared_ptr<GameComponent> SuperGameObject::GetComponent(const std::string& type) const
{
    return std::shared_ptr<GameComponent>();
}

