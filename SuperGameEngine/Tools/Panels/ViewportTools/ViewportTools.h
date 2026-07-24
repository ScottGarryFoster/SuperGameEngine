#pragma once
#include "FatedQuestLibraries.h"
#include "ViewportToolsType.h"

namespace SuperGameTools
{
    /// <summary>
    /// The tools which accompany the scene viewport.
    /// </summary>
    class ViewportTools
    {
    public:

        /// <summary>
        /// Gets the currently selected tool.
        /// </summary>
        /// <returns>The selected tool. </returns>
        virtual ViewportToolsType GetSelectedTool() const = 0;

        /// <summary>
        /// Selects a new tool.
        /// </summary>
        /// <param name="newValue">New tool to select. </param>
        virtual void SelectTool(ViewportToolsType newValue) = 0;

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Draw the viewport tools bar. 
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// Invoked when selected tool is changed.
        /// </summary>
        /// <returns>Invoked when selected tool is changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEvent> OnSelectedToolChanged() const = 0;

        /// <summary>
        /// Invoked when debug options changed.
        /// Uses ViewportDebugOptionsChanged Event Arguments.
        /// </summary>
        /// <returns>Invoked when debug options changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEvent> OnDebugOptionsChanged() const = 0;
    };
}
