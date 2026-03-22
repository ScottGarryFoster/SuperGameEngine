#pragma once
#include "Structural/Spatial/Area/RectangleInt.h"

namespace SuperGameTools
{
    /// <summary>
    /// Objects which allow the viewport engine and the panel which renders it to communicate information.
    /// </summary>
    class ViewportEngineAndPanelCommunication
    {
    public:

        ViewportEngineAndPanelCommunication();

        /// <summary>
        /// The last known location of the viewport location with the size.
        /// Best used for mouse collision.
        /// </summary>
        /// <returns>The last known location of the viewport location with the size. </returns>
        SuperGameEngine::RectangleInt GetViewportLocation() const;

        /// <summary>
        /// Update the viewport location.
        /// </summary>
        /// <param name="x">X position in the window. </param>
        /// <param name="y">Y position in the window. </param>
        /// <param name="width">Width in the window. </param>
        /// <param name="height">Height in the window. </param>
        void UpdateViewportLocation(int x, int y, int width, int height);

    private:

        /// <summary>
        /// The viewport location and size.
        /// </summary>
        SuperGameEngine::RectangleInt m_viewport;
    };
}
