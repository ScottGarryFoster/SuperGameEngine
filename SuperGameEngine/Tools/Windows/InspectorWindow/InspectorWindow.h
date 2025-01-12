#pragma once
#include "../../ToolsEngine/ViewElements/Window/WindowElement.h"
#include "../UpdateableObject/UpdateableObject.h"
#include "../../FatedQuestLibraries.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class GameObject;
    class TreeView;

    /// <summary>
    /// Property and metadata inspector window.
    /// </summary>
    class InspectorWindow : public UpdateableObject, public WindowElement, public FEventObserver
    {
    public:
        InspectorWindow();

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
        virtual void TearDown() override;

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
        /// Technically the inspector window can fail to setup if parts of the window package
        /// are not found. True means setup and these should exist.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// If we have a game object this is the game object we are displaying.
        /// </summary>
        std::shared_ptr<GameObject> m_currentGameObject;

        /// <summary>
        /// If we cannot display something for a good reason, this is displayed instead.
        /// </summary>
        std::string m_errorMessage;

        /// <summary>
        /// Create a tree view from a game object.
        /// </summary>
        /// <param name="gameObject">Game object to use as a source. </param>
        void CreateTreeFromObject(const std::shared_ptr<GameObject>& gameObject);
    };
}


