#include "ToolsCrossEngineObjects.h"

#include "OnSceneUpdatedEventArguments.h"
#include "../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsCrossEngineObjects::ToolsCrossEngineObjects()
{
    m_onNewScene = std::make_shared<FEvent>();
}

void ToolsCrossEngineObjects::Reset()
{
    m_scene = nullptr;
    m_windowPackage = nullptr;
}

std::shared_ptr<Scene> ToolsCrossEngineObjects::GetScene() const
{
    return m_scene;
}

void ToolsCrossEngineObjects::SetScene(const std::shared_ptr<Scene>& scene)
{
    bool sceneIsNew = false;
    if (m_scene != scene)
    {
        sceneIsNew = true;
    }
    m_scene = scene;

    if (sceneIsNew)
    {
        m_onNewScene->Invoke(std::make_shared<OnSceneUpdatedEventArguments>(SceneUpdateAction::NewScene));
    }
}

std::shared_ptr<FEventSubscriptions> ToolsCrossEngineObjects::OnNewScene() const
{
    return m_onNewScene;
}

std::shared_ptr<WindowPackage> ToolsCrossEngineObjects::GetWindowPackage() const
{
    return m_windowPackage;
}

void ToolsCrossEngineObjects::SetWindowPackage(const std::shared_ptr<WindowPackage>& newValue)
{
    m_windowPackage = newValue;
}

const std::shared_ptr<SuperGameEngine::TextureManager> ToolsCrossEngineObjects::GetEngineTextureManager() const
{
    return m_engineTextureManager;
}

void ToolsCrossEngineObjects::SetEngineTextureManager(const std::shared_ptr<SuperGameEngine::TextureManager>& newValue)
{
    m_engineTextureManager = newValue;
}
