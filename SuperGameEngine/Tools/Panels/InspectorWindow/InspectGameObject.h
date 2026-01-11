#pragma once
#include <memory>
#include <string>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

namespace FatedQuestLibraries
{
    class FEvent;
    class FEventSubscriptions;
    class Guid;
    class FEventArguments;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class Component;
    class TreeViewItem;
    class TreeView;
    class WindowPackage;
    class GameObject;

    /// <summary>
    /// Inspect window functionality when inspecting a GameObject
    /// </summary>
    class InspectGameObject : public FEventObserver
    {
    public:
        InspectGameObject();

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        void Setup(const std::shared_ptr<WindowPackage>& windowPackage);

        /// <summary>
        /// Called every frame.
        /// </summary>
        void Update();

        /// <summary>
        /// Called on draw.
        /// </summary>
        void Draw();

        /// <summary>
        /// Called on destroy.
        /// </summary>
        void TearDown();

        /// <summary>
        /// Called when the user has requested to delete a component.
        /// </summary>
        /// <returns>Called when the user has requested to delete a component. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnMenuDelete() const;

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
        /// Component tree view.
        /// </summary>
        std::shared_ptr<TreeView> m_components;

        /// <summary>
        /// If we are displaying a game object, this is the Game Object.
        /// </summary>
        std::shared_ptr<GameObject> m_gameObject;

        /// <summary>
        /// Technically the inspector window can fail to setup if parts of the window package
        /// are not found. True means setup and these should exist.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// If we cannot display something for a good reason, this is displayed instead.
        /// </summary>
        std::string m_errorMessage;

        /// <summary>
        /// Called when the user has requested to delete a component.
        /// </summary>
        std::shared_ptr<FEvent> m_onMenuDeleteComponent;

        /// <summary>
        /// Create a tree view from a game object.
        /// </summary>
        /// <param name="gameObject">Game object to use as a source. </param>
        void CreateTreeFromObject(const std::shared_ptr<GameObject>& gameObject);

        /// <summary>
        /// Draw the context window for the non-component section.
        /// </summary>
        void DrawInspectContextWindow();

        /// <summary>
        /// Create a component as a tree from the component data.
        /// </summary>
        /// <param name="component">Component. </param>
        /// <returns>Tree view item from the component. </returns>
        std::shared_ptr<TreeViewItem> CreateComponentTreeViewItemFromComponent(const std::shared_ptr<Component>& component);

        /// <summary>
        /// Occurs when Selection Changed
        /// </summary>
        void OnSelectionChanged();

        /// <summary>
        /// Deletes component.
        /// </summary>
        /// <param name="treeViewItemGuid">Guid of the Tree View Item. </param>
        /// <param name="component">Component to delete. </param>
        void OnDeleteComponent(const std::shared_ptr<Guid>& treeViewItemGuid, const std::shared_ptr<Component>& component);
    };
}

