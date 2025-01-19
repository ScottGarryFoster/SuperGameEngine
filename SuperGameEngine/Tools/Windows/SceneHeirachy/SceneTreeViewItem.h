#pragma once
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"
#include "../../FatedQuestLibraries.h"
#include "../../../../FatedQuest.Libraries/Observer/FEvent.h"

namespace SuperGameTools
{
    class GameObjectTreeViewItem;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class Scene;

    /// <summary>
    /// A tree view item representing a tree view item.
    /// </summary>
    class SceneTreeViewItem : public TreeViewItem, public FEventObserver
    {
    public:
        explicit SceneTreeViewItem(const std::shared_ptr<ContentManager>& contentManager);

        /// <summary>
        /// The scene attached to the Tree view item.
        /// </summary>
        /// <returns>The scene attached to the Tree view item. </returns>
        std::shared_ptr<Scene> GetScene() const;

        /// <summary>
        /// Set the scene attached to the Tree view item.
        /// </summary>
        /// <param name="scene">New scene. </param>
        void SetScene(const std::shared_ptr<Scene>& scene);

        /// <summary>
        /// Get children but as GameObject Tree view items.
        /// </summary>
        /// <returns>Get children but as GameObject Tree view items. </returns>
        /// <remarks>
        /// This is entirely self enforced.
        /// The owner of this needs to ensure that children and GO children are in line.
        /// </remarks>
        std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<GameObjectTreeViewItem>>>> GetChildrenAsGameObjects() const;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;

    private:
        /// <summary>
        /// The Scene attached to the Tree view item.
        /// </summary>
        std::shared_ptr<Scene> m_scene;

        /// <summary>
        /// Children of the tree view item.
        /// </summary>
        std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<GameObjectTreeViewItem>>>> m_gameObjectChildren;
    };
}
