#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "../../ToolsEngine/ViewElements/Window/WindowElement.h"
#include "../UpdateableObject/UpdateableObject.h"

namespace SuperGameTools
{
    class Component;
    class GameObject;
}

namespace SuperGameTools
{
    class SelectionChangedEventArguments;
    class DocumentActionEventArguments;
    class TreeViewItemOnSelectedEventArguments;
    class GameObjectTreeViewItem;
}

namespace FatedQuestLibraries
{
    class Guid;
}

namespace SuperGameTools
{
    class SceneTreeViewItem;
    class Scene;
    class SceneDocument;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class TreeViewItem;
    class TreeView;
    class SceneLoader;

    /// <summary>
    /// Contains the scenes and game objects.
    /// </summary>
    class SceneHierarchy : public UpdateableObject, public FEventObserver, public WindowElement
    {
    public:
        SceneHierarchy();
        virtual ~SceneHierarchy() override = default;

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(const std::shared_ptr<WindowPackage>& windowPackage) override;

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Called on draw.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Called on destroy.
        /// </summary>
        virtual void TearDown() override {}

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;
    private:
        /// <summary>
        /// Everything a Window Package might need to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// The tree.
        /// </summary>
        std::shared_ptr<TreeView> m_tree;

        /// <summary>
        /// Loads scene for the Tools.
        /// </summary>
        std::shared_ptr<SceneLoader> m_sceneLoader;

        /// <summary>
        /// All items in the tree.
        /// </summary>
        std::shared_ptr<TreeViewItem> m_treeViewItem;

        /// <summary>
        /// All items in the tree.
        /// </summary>
        std::shared_ptr<SceneTreeViewItem> m_sceneTreeViewItem;

        /// <summary>
        /// The current open document.
        /// </summary>
        /// <remark>
        /// Will change when we add multi-scenes to a vector.
        /// </remark>
        std::shared_ptr<SceneDocument> m_sceneDocument;

        /// <summary>
        /// Holds the scene.
        /// </summary>
        std::shared_ptr<Scene> m_scene;

        /// <summary>
        /// The top level game object tree view items in the current scene.
        /// </summary>
        std::vector<std::shared_ptr<GameObjectTreeViewItem>> m_gameObjectTreeViewItems;

        /// <summary>
        /// Loads a scene from file.
        /// This will not add a scene it simply loads it as the only scene.
        /// </summary>
        /// <param name="document">Scene document. </param>
        /// <returns>True means loaded. </returns>
        bool LoadScene(const std::shared_ptr<SceneDocument>& document);

        /// <summary>
        /// Stop selecting all tree view items but the given.
        /// </summary>
        /// <param name="treeViewItem">Item to remain selected. </param>
        /// <param name="root">Root to select from. </param>
        void RemoveSelectionFromAllBut(const std::shared_ptr<TreeViewItem>& treeViewItem, const std::shared_ptr<TreeViewItem>& root);

        /// <summary>
        /// Save all the scenes open.
        /// </summary>
        void SaveAllScenes();

        /// <summary>
        /// Occurs when TreeViewItem is selected.
        /// </summary>
        /// <param name="arguments">Event arguments. </param>
        void OnTreeViewItemOnSelectedEvent(const std::shared_ptr<TreeViewItemOnSelectedEventArguments>& arguments);

        /// <summary>
        /// Occurs when a document action happens which may require a scene load.
        /// </summary>
        /// <param name="arguments">Event arguments. </param>
        void OnDocumentActionEvent(const std::shared_ptr<DocumentActionEventArguments>& arguments);

        /// <summary>
        /// Occurs when a selection is changed, to ensure outside events can affect us.
        /// </summary>
        /// <param name="arguments">Event arguments. </param>
        void OnSelectionChangedEvent(const std::shared_ptr<SelectionChangedEventArguments>& arguments);

        /// <summary>
        /// Draw the context menu across the entire window.
        /// </summary>
        void DrawWindowWideContextClickMenu();

        /// <summary>
        /// Creates a new game object.
        /// </summary>
        void CreateNewGameObject();

        /// <summary>
        /// Deletes a game object from the hierarchy.
        /// </summary>
        /// <param name="treeViewItem">Guid of the tree view item. </param>
        /// <param name="gameObject">GameObject to remove. </param>
        void DeleteGameObject(const std::shared_ptr<Guid>& treeViewItem, const std::shared_ptr<GameObject>& gameObject);

        /// <summary>
        /// Deletes a component.
        /// </summary>
        /// <param name="gameObject">Game Object to delete on. </param>
        /// <param name="component">Component to delete. </param>
        void DeleteComponent(const std::shared_ptr<GameObject>& gameObject, const std::shared_ptr<Component>& component);

        /// <summary>
        /// Deletes a component.
        /// </summary>
        /// <param name="component">Component to delete. </param>
        void DeleteComponent(const std::shared_ptr<Component>& component);

        /// <summary>
        /// Unselects anything in current scene.
        /// </summary>
        void UnselectAll();

        bool m_testPopup;
        std::string m_testPopupText;
    };
}


