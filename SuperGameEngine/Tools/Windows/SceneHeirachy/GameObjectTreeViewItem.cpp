#include "GameObjectTreeViewItem.h"

using namespace SuperGameTools;

GameObjectTreeViewItem::GameObjectTreeViewItem(const std::shared_ptr<ContentManager>& contentManager) : TreeViewItem(contentManager)
{

}

std::shared_ptr<GameObject> GameObjectTreeViewItem::GetGameObject() const
{
    return m_gameObject;
}

void GameObjectTreeViewItem::SetGameObject(const std::shared_ptr<GameObject>& gameObject)
{
    m_gameObject = gameObject;
}
