#pragma once
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"

namespace SuperGameTools
{
    class GameObject;

    /// <summary>
    /// A tree view item representing a tree view item.
    /// </summary>
    class GameObjectTreeViewItem : public TreeViewItem
    {
    public:
        GameObjectTreeViewItem(const std::shared_ptr<ContentManager>& contentManager);

        /// <summary>
        /// The game object attached to the Tree view item.
        /// </summary>
        /// <returns>The game object attached to the Tree view item. </returns>
        std::shared_ptr<GameObject> GetGameObject() const;

        /// <summary>
        /// Set the game object attached to the Tree view item.
        /// </summary>
        /// <param name="gameObject">New game object. </param>
        void SetGameObject(const std::shared_ptr<GameObject>& gameObject);

    private:
        /// <summary>
        /// The game object attached to the Tree view item.
        /// </summary>
        std::shared_ptr<GameObject> m_gameObject;
    };
}
