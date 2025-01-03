#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "../UpdateableObject/UpdateableObject.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class TreeViewItem;
    class TreeView;
    class SceneLoader;

    /// <summary>
    /// Contains the scenes and game objects.
    /// </summary>
    class SceneHierarchy : public UpdateableObject, public FEventObserver
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
        virtual void Update() override {}

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

        bool m_testPopup;
        std::string m_testPopupText;
    };
}


