#pragma once
#include <string>

namespace SuperGameEngine
{
    /// <summary>
    /// Defines and communicates engine level changes.
    /// This is separate from ProjectProperties in that, those are developer assigned values which may set values
    /// such as the default viewport size, however this class allows you to define changes without those affecting
    /// these default values. For instance, changes to the window size might change the viewport without affecting
    /// what the default in properties is.
    /// </summary>
    class EngineControls
    {
    public:

        /// <summary>
        /// A unique name for the current engine running.
        /// Most important for the tools when there are multiple viewports outputting to textures.
        /// </summary>
        /// <returns>A unique name for the current engine running. </returns>
        virtual std::string GetName() const = 0;

        /// <summary>
        /// Set the new size for the viewport.
        /// If rendered in the tools this will define the size of the texture rendered.
        /// </summary>
        /// <param name="width">Width of the window. </param>
        /// <param name="height">Height of the window. </param>
        /// <remarks>Note that negative values will cause this method to do nothing. </remarks>
        virtual void SetNewViewportSize(int width, int height) = 0;
    };
}
