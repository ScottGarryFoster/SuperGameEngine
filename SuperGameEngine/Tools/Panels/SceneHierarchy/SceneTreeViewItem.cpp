#include "SceneTreeViewItem.h"
#include "../../GameEngineEquivalents/Scene/Scene.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"

using namespace SuperGameTools;

SceneTreeViewItem::SceneTreeViewItem(const std::shared_ptr<ContentManager>& contentManager) :
        TreeViewItem(contentManager),
        FatedQuestLibraries::FEventObserver()
{
    m_gameObjectChildren = std::make_shared<ValueProperty<std::vector<std::shared_ptr<GameObjectTreeViewItem>>>>(
        "GameObjectChildren", std::vector<std::shared_ptr<GameObjectTreeViewItem>>());
}

std::shared_ptr<Scene> SceneTreeViewItem::GetScene() const
{
    return m_scene;
}

void SceneTreeViewItem::SetScene(const std::shared_ptr<Scene>& scene)
{
    if (m_scene)
    {
        m_scene->OnDirtyFlagChanged()->Unsubscribe(FEventObserver::GetWeakDistributed());
    }

    m_scene = scene;
    m_scene->OnDirtyFlagChanged()->Subscribe(FEventObserver::GetWeakDistributed());
}

std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<GameObjectTreeViewItem>>>> SceneTreeViewItem::GetChildrenAsGameObjects() const
{
    return m_gameObjectChildren;
}

void SceneTreeViewItem::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    // TODO: [#125] Add scene names.
    if (auto dirtyArgs = std::dynamic_pointer_cast<DirtiedDataEventArguments>(arguments))
    {
        if (dirtyArgs->GetDirtyFlagState())
        {
            GetLabel()->SetValue("Scene *");
        }
        else
        {
            GetLabel()->SetValue("Scene");
        }

    }
}