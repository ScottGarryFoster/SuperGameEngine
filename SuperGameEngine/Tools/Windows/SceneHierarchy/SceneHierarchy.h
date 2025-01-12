#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "../../ToolsEngine/ViewElements/Window/WindowElement.h"
#include "../UpdateableObject/UpdateableObject.h"

namespace FatedQuestLibraries
{
    class Guid;
}

namespace SuperGameTools
{
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
        /// The current open document.
        /// </summary>
        /// <remark>
        /// Will change when we add multi-scenes to a vector.
        /// </remark>
        std::shared_ptr<SceneDocument> m_sceneDocument;

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

        bool m_testPopup;
        std::string m_testPopupText;
    };
}


