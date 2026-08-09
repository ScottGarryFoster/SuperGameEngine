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
    m_windowPackage = nullptr;
    m_sharedSceneChangedEvents = nullptr;
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

std::shared_ptr<SharedSceneChangedEvents> ToolsCrossEngineObjects::GetSharedSceneChangedEvents() const
{
    return m_sharedSceneChangedEvents;
}

void ToolsCrossEngineObjects::SetSharedSceneChangedEvents(const std::shared_ptr<SharedSceneChangedEvents>& newValue)
{
    m_sharedSceneChangedEvents = newValue;
}