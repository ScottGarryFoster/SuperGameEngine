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
        /// Called when the user has requested a new game object.
        /// </summary>
        /// <returns>Called when the user has requested a new game object. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnMenuNewGameObject() const;

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

    protected:
        /// <summary>
        /// Override with a context menu if there is one for this item in the tree view.
        /// </summary>
        virtual void DrawContextMenu() override;

    private:
        /// <summary>
        /// The game object attached to the Tree view item.
        /// </summary>
        std::shared_ptr<GameObject> m_gameObject;

        /// <summary>
        /// Called when the user has requested a new game object.
        /// </summary>
        std::shared_ptr<FEvent> m_onMenuNewGameObject;
    };
}
