#include "ToolsSharedSceneChangedEvents.h"

#include "Panels/InspectorWindow/InspectorWindow.h"
#include "Panels/SceneHierarchy/SceneHierarchy.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsSharedSceneChangedEvents::ToolsSharedSceneChangedEvents(
    const std::shared_ptr<SceneHierarchy>& sceneHierarchy, 
    const std::shared_ptr<InspectorWindow>& inspector)
{
    m_sceneHierarchy = sceneHierarchy;
    m_inspector = inspector;
}

std::shared_ptr<FEventSubscriptions> ToolsSharedSceneChangedEvents::OnComponentAdded() const
{
    return m_inspector->OnMenuAddComponent();
}

std::shared_ptr<FEventSubscriptions> ToolsSharedSceneChangedEvents::OnComponentDeleted() const
{
    return m_inspector->OnMenuDelete();
}

std::shared_ptr<FEventSubscriptions> ToolsSharedSceneChangedEvents::OnGameObjectAdded() const
{
    return m_sceneHierarchy->OnGameObjectAdded();
}

std::shared_ptr<FEventSubscriptions> ToolsSharedSceneChangedEvents::OnGameObjectDeleted() const
{
    return m_sceneHierarchy->OnGameObjectDeleted();
}

std::shared_ptr<FEventSubscriptions> ToolsSharedSceneChangedEvents::OnSceneLoaded() const
{
    return m_sceneHierarchy->OnNewScene();
}
