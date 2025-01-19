#include "GameObjectTreeViewItem.h"

#include "../SceneHierarchy/EventArguments/OnMenuNewGameObjectEventArguments.h"

using namespace SuperGameTools;

GameObjectTreeViewItem::GameObjectTreeViewItem(
    const std::shared_ptr<ContentManager>& contentManager) :
        TreeViewItem(contentManager)
{
    m_onMenuNewGameObject = std::make_shared<FEvent>();
}

std::shared_ptr<FEventSubscriptions> GameObjectTreeViewItem::OnMenuNewGameObject() const
{
    return m_onMenuNewGameObject;
}

std::shared_ptr<GameObject> GameObjectTreeViewItem::GetGameObject() const
{
    return m_gameObject;
}

void GameObjectTreeViewItem::SetGameObject(const std::shared_ptr<GameObject>& gameObject)
{
    m_gameObject = gameObject;
}

void GameObjectTreeViewItem::DrawContextMenu()
{
    if (ImGui::BeginPopupContextItem("GameObjectTreeViewItem-ContextMenu"))
    {
        if (ImGui::MenuItem("Create new Game Object"))
        {
            auto arguments = std::make_shared<OnMenuNewGameObjectEventArguments>();
            m_onMenuNewGameObject->Invoke(arguments);
        }

        ImGui::EndPopup();
    }
}
