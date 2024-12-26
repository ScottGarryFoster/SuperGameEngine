#pragma once

namespace SuperGameTools
{
    /// <summary>
    /// Allows you to control the flow of the engine.
    /// </summary>
    class EnginePlayControl
    {
    public:
        virtual ~EnginePlayControl() = default;

        /// <summary>
        /// Stop running the engine.
        /// </summary>
        virtual void Stop() = 0;

        /// <summary>
        /// Play the game.
        /// </summary>
        virtual void Play() = 0;

        /// <summary>
        /// Allow one frame to occur then stop.
        /// </summary>
        virtual void PlayForOneFrame() = 0;

        /// <summary>
        /// True means the events should be run for the engine.
        /// </summary>
        /// <returns>True means the events should be run for the engine. </returns>
        virtual bool DoRunEvents() const = 0;

        /// <summary>
        /// True means the update should be run for the engine.
        /// </summary>
        /// <returns>True means the events should be run for the update. </returns>
        virtual bool DoRunUpdate() const = 0;

        /// <summary>
        /// True means the draw should be run for the engine.
        /// </summary>
        /// <returns>True means the events should be run for the draw. </returns>
        virtual bool DoRunDraw() const = 0;
    };
}
