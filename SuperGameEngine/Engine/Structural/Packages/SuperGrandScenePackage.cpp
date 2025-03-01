#include "SuperGrandScenePackage.h"
#include <utility>

#include "SuperSceneLoadPackage.h"

using namespace SuperGameEngine;

SuperGrandScenePackage::SuperGrandScenePackage()
{
    m_createdSceneLoadPackage = false;
    m_contentManager = {};
    m_sceneLoadPackage = {};
}

std::shared_ptr<ContentManager> SuperGrandScenePackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperGrandScenePackage::SetContentManager(const std::shared_ptr<ContentManager>& contentManager)
{
    m_contentManager = contentManager;
    AttemptToCreateAGameObjectLoadPackage();
}

std::shared_ptr<SerializableParser> SuperGrandScenePackage::GetParser() const
{
    return m_serializableParser;
}

void SuperGrandScenePackage::SetSerializableParser(const std::shared_ptr<SerializableParser>& serializableParser)
{
    m_serializableParser = serializableParser;
    AttemptToCreateAGameObjectLoadPackage();
}

std::shared_ptr<InputHandler> SuperGrandScenePackage::GetInput() const
{
    return m_inputHandler;
}

void SuperGrandScenePackage::SetInputHandler(const std::shared_ptr<InputHandler>& inputHandler)
{
    m_inputHandler = inputHandler;
    AttemptToCreateAGameObjectLoadPackage();
}

std::shared_ptr<SceneLoadPackage> SuperGrandScenePackage::GetSceneLoadPackage() const
{
    return m_sceneLoadPackage;
}

void SuperGrandScenePackage::AttemptToCreateAGameObjectLoadPackage()
{
    if (m_contentManager || m_serializableParser || m_inputHandler)
    {
        auto sceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();
        sceneLoadPackage->SetContentManager(m_contentManager);
        sceneLoadPackage->SetSerializableParser(m_serializableParser);
        sceneLoadPackage->SetInputHandler(m_inputHandler);

        m_sceneLoadPackage = sceneLoadPackage;
    }
}
