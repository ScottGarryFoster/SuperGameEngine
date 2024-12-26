#pragma once
#include "EngineFlowPlayControl.h"

namespace SuperGameTools
{
    /// <summary>
    /// Play controls for the engine for the Tools Engine.
    /// </summary>
    class ToolsEngineControl : public EngineFlowPlayControl
    {
    public:
        ToolsEngineControl();
        virtual ~ToolsEngineControl() override = default;

        /// <summary>
        /// Stop running the engine.
        /// </summary>
        virtual void Stop() override;

        /// <summary>
        /// Play the game.
        /// </summary>
        virtual void Play() override;

        /// <summary>
        /// Allow one frame to occur then stop.
        /// </summary>
        virtual void PlayForOneFrame() override;

        /// <summary>
        /// Questioned at the start of the game loop.
        /// True means the engine will be re-created.
        /// </summary>
        /// <returns>True means the engine will be re-created. </returns>
        virtual bool DoRecreate() const override;

        /// <summary>
        /// True means the events should be run for the engine.
        /// </summary>
        /// <returns>True means the events should be run for the engine. </returns>
        virtual bool DoRunEvents() const override;

        /// <summary>
        /// True means the update should be run for the engine.
        /// </summary>
        /// <returns>True means the events should be run for the update. </returns>
        virtual bool DoRunUpdate() const override;

        /// <summary>
        /// True means the draw should be run for the engine.
        /// </summary>
        /// <returns>True means the events should be run for the draw. </returns>
        virtual bool DoRunDraw() const override;

        /// <summary>
        /// Questioned at the end of the loop.
        /// True means the engine pointer will be lost and
        /// the garbage collection will collect it.
        /// </summary>
        /// <returns></returns>
        virtual bool DoDestroy() const override;

        /// <summary>
        /// Called after the events have run.
        /// Only is called if the flow mentions that the events should have run.
        /// Will be called if no events occured.
        /// </summary>
        virtual void RanEvents() override;

        /// <summary>
        /// Called after the update provided the update ran.
        /// </summary>
        virtual void RanUpdate() override;

        /// <summary>
        /// Called after the draw provided the draw ran.
        /// </summary>
        virtual void RanDraw() override;

    private:
        /// <summary>
        /// True means update should always run.
        /// </summary>
        bool m_arePlaying;

        /// <summary>
        /// True means a single event, update, draw will occur.
        /// </summary>
        bool m_playForOneFrame;

        /// <summary>
        /// To ensure a complete loop occurs this must be true.
        /// Events are the first in the loop.
        /// This ensures we do not simply do a Draw and then abandon the update next frame.
        /// </summary>
        bool m_eventsHaveRunSinceAskingForOneFrame;

        /// <summary>
        /// True when game is stopped.
        /// False when game is playing but only set at creation.
        /// </summary>
        bool m_stoppedPlayingLastFrame;

        /// <summary>
        /// True at the start.
        /// False after any operation.
        /// </summary>
        bool m_neverCreated;
    };
}
