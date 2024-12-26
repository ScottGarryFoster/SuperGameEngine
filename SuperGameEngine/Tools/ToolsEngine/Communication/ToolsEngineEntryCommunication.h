#pragma once
#include <memory>

#include "EngineEntryCommunication.h"

namespace SuperGameTools
{
    /// <summary>
    /// Tools communication with the engine.
    /// </summary>
    class ToolsEngineEntryCommunication : public EngineEntryCommunication
    {
    public:
        virtual ~ToolsEngineEntryCommunication() = default;

        /// <summary>
        /// Allows you to control the flow of the engine.
        /// </summary>
        /// <returns>Allows you to control the flow of the engine. </returns>
        virtual std::shared_ptr<EnginePlayControl> GetPlayControls() const override;

        /// <summary>
        /// Set play controls.
        /// </summary>
        /// <param name="playControls">
        /// New play controls.
        /// </param>
        void SetPlayControls(const std::shared_ptr<EnginePlayControl>& playControls);

    private:
        /// <summary>
        /// Allows you to control the flow of the engine.
        /// </summary>
        std::shared_ptr<EnginePlayControl> m_playControl;
    };
}


