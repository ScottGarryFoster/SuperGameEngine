#pragma once
#include "../UpdateableObject/UpdateableObject.h"

struct ImGuiTable;

namespace SuperGameTools
{
    /// <summary>
    /// Holds the viewport.
    /// </summary>
    class LoggerOutput : public UpdateableObject
    {
    public:
        LoggerOutput();
        virtual ~LoggerOutput();

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

    private:

        /// <summary>
        /// Services to run a window.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;
    };
}
