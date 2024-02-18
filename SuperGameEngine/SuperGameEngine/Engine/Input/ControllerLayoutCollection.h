#pragma once
#include "ControllerLayout.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Contains the Controller Layouts for the game.
    /// </summary>
    class ControllerLayoutCollection : public Object
    {
    public:
        ControllerLayoutCollection();
        ~ControllerLayoutCollection();

        /// <summary>
        /// Get controller mappings for all controllers.
        /// </summary>
        /// <returns>Controller mappings for all controllers loaded. </returns>
        FList<ControllerLayout*>* GetControllerLayouts();

    private:

        /// <summary>
        /// All Controller layouts loaded.
        /// </summary>
        FList<ControllerLayout*>* m_controllerLayout;
    };
}