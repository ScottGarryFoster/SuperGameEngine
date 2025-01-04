#pragma once
#include "../UpdateableObject/UpdateableObject.h"

namespace SuperGameTools
{
    class MenuView;

    /// <summary>
    /// Creates and manages the top main menu bar.
    /// </summary>
    class MainMenuBar : public UpdateableObject
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

    private:
        /// <summary>
        /// Entire top menu bar.
        /// </summary>
        std::shared_ptr<MenuView> m_mainView;
    };
}
