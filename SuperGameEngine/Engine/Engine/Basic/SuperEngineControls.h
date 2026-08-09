#pragma once
#include <memory>

#include "EngineControls.h"
#include "DebugEngine/DebugEngine.h"

namespace SuperGameEngine
{
    class ProjectProperties;
}

namespace SuperGameEngine
{
    /// <summary>
    /// Defines the ability to manipulate the way the engine outputs on the fly.
    /// </summary>
    class SuperEngineControls : public virtual EngineControls
    {
    public:

        SuperEngineControls(const std::string& name);

        /// <summary>
        /// A unique name for the current engine running.
        /// Most important for the tools when there are multiple viewports outputting to textures.
        /// </summary>
        /// <returns>A unique name for the current engine running. </returns>
        virtual std::string GetName() const override;

        /// <summary>
        /// Set the new size for the viewport.
        /// If rendered in the tools this will define the size of the texture rendered.
        /// </summary>
        /// <param name="width">Width of the window. </param>
        /// <param name="height">Height of the window. </param>
        /// <remarks>Note that negative values will cause this method to do nothing. </remarks>
        virtual void SetNewViewportSize(int width, int height) override;

        /// <summary>
        /// Occurs when the viewport has changed size.
        /// Uses ViewportSizeChangedEventArguments to provide information on what has changed.
        /// </summary>
        /// <returns></returns>
        std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnViewportSizeChanged() const;

    private:
        /// <summary>
        /// A unique name for the current engine running.
        /// Most important for the tools when there are multiple viewports outputting to textures.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Defines the width of the viewport.
        /// </summary>
        int m_viewportWidth;

        /// <summary>
        /// Defines the height of the viewport.
        /// </summary>
        int m_viewportHeight;

        /// <summary>
        /// Event called when the size has updated.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onViewportSizeChanged;
    };
}
