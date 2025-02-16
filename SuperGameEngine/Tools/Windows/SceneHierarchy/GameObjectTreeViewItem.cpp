#include "GameObjectTreeViewItem.h"

#include "../SceneHierarchy/EventArguments/OnMenuNewGameObjectEventArguments.h"
#include "EventArguments/OnMenuDeleteGameObjectEventArguments.h"

using namespace SuperGameTools;

GameObjectTreeViewItem::GameObjectTreeViewItem(
    const std::shared_ptr<ContentManager>& contentManager) :
        TreeViewItem(contentManager)
{
    m_onMenuNewGameObject = std::make_shared<FEvent>();
    m_onMenuDeleteGameObject = std::make_shared<FEvent>();
}

std::shared_ptr<FEventSubscriptions> GameObjectTreeViewItem::OnMenuNewGameObject() const
{
    return m_onMenuNewGameObject;
}

std::shared_ptr<FEventSubscriptions> GameObjectTreeViewItem::OnMenuDeleteGameObject() const
{
    return m_onMenuDeleteGameObject;
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
        if (ImGui::MenuItem("Delete", nullptr, nullptr, true))
        {
            auto arguments = std::make_shared<OnMenuDeleteGameObjectEventArguments>
                (GetUniqueID(), GetGameObject());
            m_onMenuDeleteGameObject->Invoke(arguments);
        }

        ImGui::EndPopup();
    }
}
