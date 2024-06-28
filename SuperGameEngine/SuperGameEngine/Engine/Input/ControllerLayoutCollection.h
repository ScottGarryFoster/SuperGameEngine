#pragma once
#include "ControllerLayout.h"
#include "../Content/PackageContents.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Contains the Controller Layouts for the game.
    /// </summary>
    class ControllerLayoutCollection : public Object
    {
    public:
        ControllerLayoutCollection(std::shared_ptr<PackageContents> packageContents);
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

        /// <summary>
        /// File access to the package without the need to worry about
        /// the package or binary formats.
        /// </summary>
        std::shared_ptr<PackageContents> m_packageContents;
    };
}