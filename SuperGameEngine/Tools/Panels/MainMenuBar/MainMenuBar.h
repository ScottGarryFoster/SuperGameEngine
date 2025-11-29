#pragma once
#include <string>
#include <unordered_map>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "../UpdateableObject/UpdateableObject.h"

namespace SuperGameTools
{
    class MenuView;

    /// <summary>
    /// Creates and manages the top main menu bar.
    /// </summary>
    class MainMenuBar : public UpdateableObject, public FatedQuestLibraries::FEventObserver
    {
    public:
        virtual ~MainMenuBar() override = default;

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
        /// Gets the top menu bar.
        /// </summary>
        /// <returns>The top menu bar. </returns>
        std::shared_ptr<MenuView> GetTopMenuBar() const;

        /// <summary>
        /// Ran after all panels have been added to create or setup options which need
        /// to be hooked up to panels.
        /// </summary>
        void SetupPostPanels() const;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

    private:
        /// <summary>
        /// Entire top menu bar.
        /// </summary>
        std::shared_ptr<MenuView> m_mainView;

        /// <summary>
        /// Everything a Window Package might need to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// The menu items which should be directly linked to panel items.
        /// This should not be needed for the windows/layout options but instead for
        /// the other locations those panels are found. For instance File->Project Properties
        /// opens a panel, even though it and anything else is also open-able in the window menu.
        /// </summary>
        std::unordered_map<std::string, std::string> m_openPanelMenuItems;

        bool TryToOpenPanel(const std::string& key) const;
    };
}
