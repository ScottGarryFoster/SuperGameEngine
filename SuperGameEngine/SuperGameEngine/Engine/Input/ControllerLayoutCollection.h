#pragma once
#include "ControllerLayout.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Contains the Controller Layouts for the game.
    /// </summary>
    class ControllerLayoutCollection
    {
    public:
        ControllerLayoutCollection();
        ~ControllerLayoutCollection();

        FList<ControllerLayout*>* GetControllerLayouts();

    private:

        /// <summary>
        /// All Controller layouts loaded.
        /// </summary>
        FList<ControllerLayout*>* m_controllerLayout;

        ControllerLayout* ReturnXboxPadLayout(bool xboxOne = false);
        ControllerLayout* ReturnSwitchProLayout();
    };
}