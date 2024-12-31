#include "SuperSceneLoadPackage.h"
#include "../../Engine/Content/ContentManager.h"
#include "SuperGameObjectLoadPackage.h"

using namespace SuperGameEngine;

SuperSceneLoadPackage::SuperSceneLoadPackage()
{
    m_contentManager = {};
}

std::shared_ptr<ContentManager> SuperSceneLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperSceneLoadPackage::SetContentManager(const std::shared_ptr<ContentManager>& contentManager)
{
    m_contentManager = contentManager;
    AttemptToCreateASceneLoadPackage();
}

std::shared_ptr<SerializableParser> SuperSceneLoadPackage::GetParser() const
{
    return m_serializableParser;
}

void SuperSceneLoadPackage::SetSerializableParser(
    const std::shared_ptr<SerializableParser>& serializableParser)
{
    m_serializableParser = serializableParser;
    AttemptToCreateASceneLoadPackage();
}

std::shared_ptr<GameObjectLoadPackage> SuperSceneLoadPackage::GetGameObjectLoadPackage() const
{
    return m_gameObjectLoadPackage;
}

void SuperSceneLoadPackage::AttemptToCreateASceneLoadPackage()
{
    if (m_contentManager || m_serializableParser)
    {
        auto sceneLoadPackage = std::make_shared<SuperGameObjectLoadPackage>();
        sceneLoadPackage->SetContentManager(m_contentManager);
        sceneLoadPackage->SetSerializableParser(m_serializableParser);

        m_gameObjectLoadPackage = sceneLoadPackage;
    }
}
