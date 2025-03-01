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

std::shared_ptr<InputHandler> SuperSceneLoadPackage::GetInput() const
{
    return m_inputHandler;
}

void SuperSceneLoadPackage::SetInputHandler(const std::shared_ptr<InputHandler>& inputHandler)
{
    m_inputHandler = inputHandler;
    AttemptToCreateASceneLoadPackage();
}

std::shared_ptr<GameObjectLoadPackage> SuperSceneLoadPackage::GetGameObjectLoadPackage() const
{
    return m_gameObjectLoadPackage;
}

void SuperSceneLoadPackage::AttemptToCreateASceneLoadPackage()
{
    if (m_contentManager || m_serializableParser || m_inputHandler)
    {
        auto sceneLoadPackage = std::make_shared<SuperGameObjectLoadPackage>();
        sceneLoadPackage->SetContentManager(m_contentManager);
        sceneLoadPackage->SetSerializableParser(m_serializableParser);
        sceneLoadPackage->SetInputHandler(m_inputHandler);

        m_gameObjectLoadPackage = sceneLoadPackage;
    }
}
