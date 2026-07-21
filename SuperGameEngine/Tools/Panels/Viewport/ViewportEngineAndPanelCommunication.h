#pragma once
#include "Structural/Spatial/Area/RectangleInt.h"

namespace SuperGameTools
{
    class ViewportTools;

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

        /// <summary>
        /// Gives this communication object the Viewport Tools.
        /// Viewport Tools are the controls within the game viewport, things like pointer and move.
        /// </summary>
        /// <param name="viewportTools">
        /// Viewport Tools are the controls within the game viewport, things like pointer and move.
        /// </param>
        void GiveViewportTools(const std::shared_ptr<ViewportTools>& viewportTools);

        /// <summary>
        /// Viewport Tools are the controls within the game viewport, things like pointer and move.
        /// </summary>
        /// <returns>
        /// Viewport Tools are the controls within the game viewport, things like pointer and move.
        /// </returns>
        std::shared_ptr<ViewportTools> GetViewportTools() const;

    private:

        /// <summary>
        /// The viewport location and size.
        /// </summary>
        SuperGameEngine::RectangleInt m_viewport;

        /// <summary>
        /// Viewport Tools are the controls within the game viewport, things like pointer and move.
        /// </summary>
        std::shared_ptr<ViewportTools> m_viewportTools;
    };
}
